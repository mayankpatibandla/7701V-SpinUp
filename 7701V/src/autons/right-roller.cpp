#include "auton-manager.h"

void autons::rightRoller() {
  flyMtrs.spin(fwd, 0.875 * 12, volt);
  angler.set(true);

  // roller
  driveRelative(23, 300, 1700);
  turnToAngle(-M_PI_2 + 0.1, 600, 1500);

  driveRelative(4, 150, 500);
  intakeMtrs.spin(fwd, -12, volt);
  this_thread::sleep_for(275);
  intakeMtrs.stop(brake);

  driveRelative(-3, 0, 500);
}