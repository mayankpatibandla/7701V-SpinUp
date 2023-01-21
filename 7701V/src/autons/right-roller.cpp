#include "auton-manager.h"

void autons::rightRoller() {
  flyMtrs.spin(fwd, 0.875 * 12, volt);
  angler.set(true);

  // roller
  driveRelative(23, 300, 1700);
  turnToAngle(-M_PI_2 + 0.1, 600, 1500);

  driveRelative(4, 150, 500);
  intakeMtrs.spin(fwd, -12, volt);
  this_thread::sleep_for(350);
  intakeMtrs.stop(brake);

  driveRelative(-3, 0, 500);

  // shoot preloads
  turnToAngle(-1.78, 100, 700);
  Indexer.shootDisc();
  this_thread::sleep_for(2000);
  Indexer.shootDisc();
  this_thread::sleep_for(500);

  // intake more discs
  // 2.67, 2.46, -2.28
  intakeMtrs.spin(fwd, 12, volt);
  flyMtrs.spin(fwd, 0.775 * 12, volt);

  turnToAngle(2.67, 250, 1000);
  driveRelative(25, 300, 1000, {.0005, 0.000001, 0.000005});

  turnToAngle(2.46, 250, 1000);
  driveRelative(50, 400, 1500, {.0005, 0.000001, 0.000005});

  //shoot discs
  turnToAngle(-2.28, 300, 1000);
  Indexer.shootDisc();
  this_thread::sleep_for(1000);
  Indexer.shootDisc();
  this_thread::sleep_for(1000);
  Indexer.shootDisc();
}