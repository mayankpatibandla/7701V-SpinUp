#include "auton-manager.h"

void auton_leftHighGoal() {
  flyMtrs.spin(fwd, 12, volt);

  intakeMtrs.spin(fwd, -12, volt);
  driveMtrs.spinFor(90, deg, 50, velocityUnits::pct);
  this_thread::sleep_for(197);
  intakeMtrs.stop(brake);

  driveMtrs.spinFor(-100, deg, 50, velocityUnits::pct);

  leftDriveMtrs.spin(fwd, -3, volt);
  rightDriveMtrs.spin(fwd, 3, volt);
  this_thread::sleep_for(250);
  driveMtrs.stop();
  
  this_thread::sleep_for(3500);
  Indexer.shootDisc();
  this_thread::sleep_for(2000);
  Indexer.shootDisc();
  this_thread::sleep_for(1000);
  Indexer.shootDisc();
  this_thread::sleep_for(2000);
}