#include "control.h"

void expand(){
  leftExpansion.toggle();
  rightExpansion.toggle();
}

void turnToAngle(double theta, int minTime, int maxTime, PID pid) {
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
    pow = clamp(pow, -1., 1.);

    leftDriveMtrs.spin(fwd, -pow * 12, volt);
    rightDriveMtrs.spin(fwd, pow * 12, volt);

    std::cout << "kP: " << pid.kP << " kI: " << pid.kI << " kD: " << pid.kD
              << std::endl;
    std::cout << "Pow: " << pow << " Err: " << error << std::endl;

    // sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMtrs.stop(brake);
  std::cout << "Done"
            << " Time: " << turnTimer.time(msec) << std::endl;
}

void driveRelative(double distance, int minTime, int maxTime, PID pid) {
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
    pow = clamp(pow, -1., 1.);

    driveMtrs.spin(fwd, pow * 12, volt);

    // debug
    std::cout << "kP: " << pid.kP << " kI: " << pid.kI << " kD: " << pid.kD
              << std::endl;
    std::cout << "Pow: " << pow << " Err: " << error << std::endl;

    // sleep for dT
    this_thread::sleep_until(timeStart + pid.dT);
  }
  driveMtrs.stop(brake);
  std::cout << "Done"
            << " Time: " << driveTimer.time(msec) << std::endl;
}

std::vector<double> getHighGoalCoords(highGoal goal) {
  if (selectedAuton.side == LEFT) {
    switch (goal) {
    case RED_HIGHGOAL: {
      // return std::vector<double>{-11, 118};
      return std::vector<double>{0, 0};
    } break;
    case BLUE_HIGHGOAL: {
      return std::vector<double>{0, 0};
    } break;
    }
  } else if (selectedAuton.side == RIGHT) {
    switch (goal) {
    case RED_HIGHGOAL: {
      return std::vector<double>{0, 0};
    } break;
    case BLUE_HIGHGOAL: {
      return std::vector<double>{0, 0};
    } break;
    }
  }

  return std::vector<double>(0);
}

void aimHighGoal(PID pid, highGoal goal, bool &autoAiming) {
  while (true) {
    timer turnTimer;
    turnTimer.reset();

    std::vector<double> highGoalPos = getHighGoalCoords(goal);

    double pow = 1 / 0.;

    double error = 1 / 0.;
    double integral = 0;
    double derivative = 0;

    double prevError = error;

    const double errorAcc = 0.075, powAcc = 0.15;

    // update target pos
    // ? should this be inside loop
    double theta = atan2(pt::y() - highGoalPos[1], pt::x() - highGoalPos[0]);

    while (autoAiming &&
           (std::abs(error) > errorAcc || std::abs(pow) > powAcc)) {
      uint32_t timeStart = Brain.Timer.system();

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
      pow = clamp(pow, -1., 1.);

      leftDriveMtrs.spin(fwd, -pow * 12, volt);
      rightDriveMtrs.spin(fwd, pow * 12, volt);

      // debug
      std::cout << "kP: " << pid.kP << " kI: " << pid.kI << " kD: " << pid.kD
                << std::endl;
      std::cout << "Pow: " << pow << " Err: " << error << std::endl;

      // sleep for dT
      this_thread::sleep_until(timeStart + pid.dT);
    }

    this_thread::sleep_for(5);
  }
}

double calcFlywheelCoeff(highGoal goal) {
  return 0;
}