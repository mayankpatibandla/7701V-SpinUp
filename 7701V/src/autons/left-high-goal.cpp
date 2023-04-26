#include "control/control.hpp"

void autons::leftHighGoal() {
  Flywheel.setTargetVelocity(1);
  intakeMtrs.spin(fwd, 12, volt);
  angler.set(true);

  // get disc
  turnToAngle(-0.775, 0, 1000);
  driveRelative(11, 75, 900, 0.75);
  this_thread::sleep_for(1000);
  driveRelative(-3, 50, 500);

  // roller
  turnToAngle(M_PI_2, 0, 1000);
  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165, 500);
  Flywheel.setTargetVelocity(0.7);
  driveRelative(-4, 0, 600);

  // knock over 3 stack
  turnToAngle(0.46, 0, 1000);
  driveRelative(-30, 0, 1200, 0.7);

  // shoot
  turnToAngle(2.3, 100, 1200, 0.6, {0.375, 0, 0});
  repeat(3) {
    Indexer.shootDisc();
    Flywheel.setTargetVelocity(0.77);
    this_thread::sleep_for(500);
  }
}