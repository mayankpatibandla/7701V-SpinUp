#include "config/auton-manager.hpp"
#include "control/control.hpp"

void autons::rightHighGoal() {
  flyMtrs.spin(fwd, 12, volt);
  angler.set(true);

  // roller
  driveRelative(21, 300, 1700);
  turnToAngle(-M_PI_2 + 0.1, 600, 1200);

  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165);

  driveRelative(-2.4166, 0, 1000);

  // get disc
  turnToAngle(2.65, 300, 1500, 0.7);
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(35, 100, 2000, 0.85);
}