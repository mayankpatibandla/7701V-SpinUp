#include "config/auton-manager.hpp"
#include "control/control.hpp"

void autons::rightRoller() {
  driveRelative(23, 300, 1700);
  turnToAngle(-M_PI_2 + 0.1, 600, 1200);

  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165);

  driveRelative(-2.4166, 0, 1000);
}