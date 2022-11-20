#include "auton-manager.h"

void autons::rightHighGoal() {
  flyMtrs.spin(fwd, 12, volt);

  driveRelative(25.75, 1200, 2000);
  turnToAngle(-M_PI_2, 1000, 1700, {2.15, 0, 0.025});

  driveRelative(5, 200, 600);
  intakeMtrs.spin(fwd, -12, volt);
  this_thread::sleep_for(150);
  intakeMtrs.stop(brake);

  driveRelative(-5, 0, 700);
  turnToAngle(-1.78, 300, 700, {2.16, 0, 0.025});

  driveRelative(2, 0, 300);

  Indexer.shootDisc();
  this_thread::sleep_for(1000);
  Indexer.shootDisc();
  this_thread::sleep_for(1000);

  flyMtrs.stop(coast);
}