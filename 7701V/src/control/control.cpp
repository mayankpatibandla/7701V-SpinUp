#include "control/control.hpp"

bool matchLoadEnabled = false;

void matchLoad() {
  while (true) {
    if (matchLoadEnabled) {
      if (storageDistMin < storageDistance.objectDistance(mm) &&
          storageDistance.objectDistance(mm) < storageDistMax) {
        this_thread::sleep_for(matchLoadStartDelay);
        waitUntil(std::abs(Flywheel.velocity(pct) / 100) > flywheelMinCoeff ||
                  !matchLoadEnabled);
        if (matchLoadEnabled) {
          Indexer.shootDisc();
        }
        this_thread::sleep_for(matchLoadEndDelay);
      }
    }
    this_thread::sleep_for(1);
  }
}

vex::thread matchLoadThread(matchLoad);

void expandAll() {
  topLeftExpansion.toggle();
  topRightExpansion.toggle();
  bottomLeftExpansion.toggle();
  bottomRightExpansion.toggle();
}
void expandBottom() {
  bottomLeftExpansion.toggle();
  bottomRightExpansion.toggle();
}
void expandTop() {
  topLeftExpansion.toggle();
  topRightExpansion.toggle();
}
void expandLeft() { bottomLeftExpansion.toggle(); }
void expandRight() { bottomRightExpansion.toggle(); }

void spinRoller(double velocity, color col, int minTime, int maxTime) {
  timer rollerTimer;
  rollerTimer.reset();

  double voltage = velocity * 12;

  intakeMtrs.spin(fwd, voltage, volt);

  waitUntil(rollerTimer.time(msec) > minTime || minTime == 0);
  while (true) {
    double leftHue = leftRollerOptical.hue();
    double rightHue = rightRollerOptical.hue();

    if (rollerTimer.time(msec) > maxTime && maxTime != 0) {
      break;
    }

    if (leftRollerOptical.isNearObject()) {
      if (col == red && (redMax > leftHue || leftHue > redMin)) {
        break;
      }

      if (col == blue && blueMax > leftHue && leftHue > blueMin) {
        break;
      }
    }

    if (rightRollerOptical.isNearObject()) {
      if (col == red && (redMax > rightHue || rightHue > redMin)) {
        break;
      }

      if (col == blue && blueMax > rightHue && rightHue > blueMin) {
        break;
      }
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

  const double errorAcc = 0.05, powAcc = 0.01;

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
      error = absError - 2 * M_PI;
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
    pow = error * pid.kP + integral * pid.kI + derivative * pid.kD;
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
      (distance / (2 * M_PI * pt::WHEEL_RADIUS)) * 360 + lRot.position(deg);

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