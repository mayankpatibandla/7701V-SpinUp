#include "auton-manager.h"

void autons::rightRoller() {
  driveRelative(23.5, 1200, 2000);
  turnToAngle(-M_PI_2, 1000, 1700, {2.15, 0, 0.025});

  driveRelative(6.5, 200, 600);
  intakeMtrs.spin(fwd, -12, volt);
  this_thread::sleep_for(150);
  intakeMtrs.stop(brake);

  driveRelative(-5, 0, 700);
  turnToAngle(-1.78, 300, 700, {2.16, 0, 0.025});
}