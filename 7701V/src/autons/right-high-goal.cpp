#include "control/control.hpp"

void autons::rightHighGoal() {
  Flywheel.setTargetVelocity(1);
  angler.set(true);

  // roller
  driveRelative(22.5, 300, 1700);
  turnToAngle(-M_PI_2 + 0.1, 600, 1200);

  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165);

  driveRelative(-2.15, 25, 200);

  // get disc
  turnToAngle(2.6, 300, 1500);
  Flywheel.setTargetVelocity(0.67);
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(38, 100, 2500);

  // shoot discs
  turnToAngle(-2.06, 100, 1200, 0.6, {0.375, 0, 0});
  repeat(3) {
    Indexer.shootDisc();
    Flywheel.setTargetVelocity(0.77);
    this_thread::sleep_for(500);
  }

  // get discs
  turnToAngle(2.34, 0, 1000);
  Flywheel.setTargetVelocity(0.6475);
  driveRelative(26, 0, 1000);
  turnToAngle(-2.2, 0, 1000);
  driveRelative(15, 0, 800);

  // shoot discs
  driveRelative(-12, 0, 1000);
  turnToAngle(-1.975, 0, 1000, 0.75, {0.425, 0, 0});
  repeat(3) {
    Indexer.shootDisc();
    Flywheel.setTargetVelocity(0.73);
    this_thread::sleep_for(500);
  }
}