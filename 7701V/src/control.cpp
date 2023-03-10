#include "control.h"

bool matchLoadEnabled = false;

void matchLoad() {
  while (true) {
    if (matchLoadEnabled) {
      if (storageDistMin < storageDistance.objectDistance(mm) &&
          storageDistance.objectDistance(mm) < storageDistMax) {
        this_thread::sleep_for(matchLoadStartDelay);
        Indexer.shootDisc();
        this_thread::sleep_for(matchLoadEndDelay);
      }
    }
    this_thread::sleep_for(1);
  }
}

vex::thread matchLoadThread(matchLoad);

void expand() {
  leftExpansion.toggle();
  rightExpansion.toggle();
}

void spinRoller(double velocity, color col, int minTime, int maxTime) {
  timer rollerTimer;
  rollerTimer.reset();

  double voltage = velocity * 12;

  intakeMtrs.spin(fwd, voltage, volt);

  waitUntil(rollerTimer.time(msec) > minTime || minTime == 0);
  while (true) {
    int hue = rollerOptical.hue();

    if (rollerTimer.time(msec) > maxTime && maxTime != 0) {
      break;
    }

    if (col == red && (redMax > hue || hue > redMin)) {
      break;
    }

    if (col == blue && blueMax > hue && hue > blueMin) {
      break;
    }

    this_thread::sleep_for(1);
  }

  intakeMtrs.stop();
}

void turnToAngle(double theta, int minTime, int maxTime, double maxVelocity,
                 PID pid) {
  timer turnTimer;
  turnTimer.reset();

  double pow = 1 / 0.;

  double error = 1 / 0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 0.075, powAcc = 0.15;

  while (std::abs(error) > errorAcc || std::abs(pow) > powAcc ||
         (turnTimer.time(msec) < minTime && minTime != 0)) {
    uint32_t timeStart = Brain.Timer.system();
    // timeout
    if (maxTime != 0 && turnTimer.time(msec) > maxTime) {
      break;
    }

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
    if (error == 0 || std::abs(currentPos) > std::abs(theta) ||
        error > pid.maxError) {
      integral = 0;
    }

    // calculate derivative and update previous error
    derivative = error - prevError;
    prevError = error;

    // output powers
    pow = error * pid.kP + integral * pid.kI + derivative + pid.kD;
    pow = clamp(pow, -maxVelocity, maxVelocity);

    leftDriveMtrs.spin(fwd, -pow * 12, volt);
    rightDriveMtrs.spin(fwd, pow * 12, volt);

    // sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMtrs.stop(brake);
}

void driveRelative(double distance, int minTime, int maxTime,
                   double maxVelocity, PID pid) {
  timer driveTimer;
  driveTimer.reset();

  distance =
      (distance / (M_TWOPI * pt::WHEEL_RADIUS)) * 360 + lRot.position(deg);

  double pow = 1 / 0.;

  double error = 1 / 0.;
  double integral = 0;
  double derivative = 0;

  double prevError = error;

  const double errorAcc = 10, powAcc = 0.15;

  while (std::abs(error) > errorAcc || std::abs(pow) > powAcc ||
         (driveTimer.time(msec) < minTime && minTime != 0)) {
    uint32_t timeStart = Brain.Timer.system();
    // timeout
    if (maxTime != 0 && driveTimer.time(msec) > maxTime) {
      break;
    }

    // update current pos
    double currentPos = lRot.position(deg);
    // calculate error
    error = distance - currentPos;

    // add error to integral
    integral += error;

    // integral windup
    if (error == 0 || std::abs(currentPos) > std::abs(distance) ||
        error > pid.maxError) {
      integral = 0;
    }

    // calculate derivative and update previous error
    derivative = error - prevError;
    prevError = error;

    // output powers
    pow = error * pid.kP + integral * pid.kI + derivative * pid.kD;
    pow = clamp(pow, -maxVelocity, maxVelocity);

    driveMtrs.spin(fwd, pow * 12, volt);

    // sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMtrs.stop(brake);
}