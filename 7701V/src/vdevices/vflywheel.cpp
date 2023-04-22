#include "vdevices/vflywheel.hpp"

vdevices::flywheel::PID::PID(double kP, double kI, double kD, double maxError,
                             double dT)
    : kP(kP), kI(kI), kD(kD), maxError(maxError), dT(dT) {}

void vdevices::flywheel::pidCore(void *arg) {
  if (arg == NULL) {
    return;
  }
  flywheel *instance = static_cast<flywheel *>(arg);

  double pow = 1 / 0.;

  double error = 1 / 0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  while (true) {
    uint32_t timeStart = timer::system();

    // update current pos
    double currentPos = instance->velocity(velocityUnits::pct) / 100.;
    // calculate error
    error = instance->getTargetVelocity() - currentPos;

    // add error to integral
    integral += error;

    // integral windup
    if (error == 0 ||
        std::abs(currentPos) > std::abs(instance->getTargetVelocity()) ||
        error > instance->pid.maxError) {
      integral = 0;
    }

    // calculate derivative and update previous error
    derivative = error - prevError;
    prevError = error;

    // output powers
    pow = error * instance->pid.kP + integral * instance->pid.kI +
          derivative * instance->pid.kD;
    pow = clamp(pow, -1.0, 1.0);

    instance->spin(
        fwd, std::abs(instance->getTargetVelocity()) > 0 ? pow * 12 : 0, volt);

    std::cout << "Pos: " << currentPos << " Pow: " << pow << std::endl;

    // sleep for dT
    this_thread::sleep_until(timeStart + instance->pid.dT);
  }
}

void vdevices::flywheel::init() {
  pidThread = vex::thread(pidCore, static_cast<void *>(this));
}

vdevices::flywheel::PID vdevices::flywheel::getPID() { return pid; }
void vdevices::flywheel::setPID(PID pid_a) { pid = pid_a; }

double vdevices::flywheel::getTargetVelocity() { return targetVel; }
void vdevices::flywheel::setTargetVelocity(double target) {
  target = clamp(target, -1.0, 1.0);
  targetVel = target;
}
