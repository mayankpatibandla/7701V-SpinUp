#include "control/control.hpp"

void autons::leftRoller() {
  driveMtrs.spinFor(fwd, 100, msec, 50, velocityUnits::pct);
  spinRoller(-1, rollerColor, 200);

  turnToAngle(0.1, 100, 500, 0.25);
}
