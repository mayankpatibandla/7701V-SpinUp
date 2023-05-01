#include "control/control.hpp"

void autons::leftHighGoal() {
  Flywheel.setTargetVelocity(1);
  angler.set(true);

  // roller
  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165, 750);
  Flywheel.setTargetVelocity(0.7);
  driveRelative(-3, 0, 350);

  // knock over 3 stack
  turnToAngle(-0.675, 0, 1000);
  driveRelative(-30, 0, 1200, 0.7);

  // shoot
  turnToAngle(2.2, 100, 1200, 0.6, {0.375, 0, 0});
  repeat(3) {
    Indexer.shootDisc();
    Flywheel.setTargetVelocity(0.77);
    this_thread::sleep_for(500);
  }
}