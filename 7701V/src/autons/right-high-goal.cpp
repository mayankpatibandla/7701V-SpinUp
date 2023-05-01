#include "control/control.hpp"

void autons::rightHighGoal() {
  Flywheel.setTargetVelocity(1);
  angler.set(true);

  // roller
  driveRelative(22.5, 300, 1700);
  turnToAngle(-1.6, 600, 1200);

  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165, 750);

  driveRelative(-2.15, 25, 200);

  // get disc
  turnToAngle(2.55, 300, 1500);
  Flywheel.setTargetVelocity(0.67);
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(38, 100, 2500);

  // shoot discs
  turnToAngle(-2.095, 100, 1200, 0.6, {0.375, 0, 0});
  shootAll(0.77, 2000);

  // get discs
  turnToAngle(2.3, 0, 1000);
  Flywheel.setTargetVelocity(0.6475);
  driveRelative(27, 0, 1000);
  turnToAngle(-2.03, 0, 1000);
  driveRelative(15, 0, 800);

  // shoot discs
  driveRelative(-12, 0, 1000);
  turnToAngle(-2.01, 0, 1000, 0.75, {0.425, 0, 0});
  shootAll(0.73, 2000);
}