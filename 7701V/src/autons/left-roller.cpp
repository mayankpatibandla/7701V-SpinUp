#include "auton-manager.h"

void auton_leftRoller() {
  intakeMtrs.spin(fwd, -12, volt);
  driveMtrs.spinFor(90, deg, 50, velocityUnits::pct);
  this_thread::sleep_for(197);
  intakeMtrs.stop(brake);

  driveMtrs.spinFor(-100, deg, 50, velocityUnits::pct);

  leftDriveMtrs.spin(fwd, -3, volt);
  rightDriveMtrs.spin(fwd, 3, volt);
  this_thread::sleep_for(250);
  driveMtrs.stop();
}