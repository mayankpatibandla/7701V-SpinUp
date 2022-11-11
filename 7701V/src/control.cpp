#include "control.h"

namespace pt = positiontracking;

void turnToAngle(double theta, int timeout, PID pid) {
  std::cout << pid.kP << " " << pid.kI << std::endl;
  timer turnTimer;
  turnTimer.reset();

  double pow = 1;

  double error = 1 / 0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.05, powAcc = 0.05;

  while (std::abs(error) > errorAcc || std::abs(pow) > powAcc) {
    uint32_t timeStart = Brain.Timer.system();
    // timeout
    if (timeout != 0 && turnTimer.time(msec) > timeout)
      break;

    // update current pos
    double currentPos = pt::thetaWrapped();
    // calculate error
    double absError = theta - currentPos;

    // angle wrap fix
    if (absError < M_PI) {
      error = absError;
    } else {
      error = absError - M_TWOPI;
    }

    // add error to integral
    integral += error;

    // integral windup
    if (error == 0 || std::abs(currentPos) > std::abs(theta)) {
      integral = 0;
    }
    if (error > pid.maxError) {
      integral = 0;
    }

    // calculate derivative and update previous error
    derivative = error - prevError;
    prevError = error;

    // output powers
    pow = error * pid.kP + integral * pid.kI + derivative * pid.kD;

    leftDriveMtrs.spin(fwd, -pow * 12, volt);
    rightDriveMtrs.spin(fwd, pow * 12, volt);

    // sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMtrs.stop();
}