#include "auton-manager.h"
#include "control.h"

void autons::leftRoller() {
  driveMtrs.spinFor(fwd, 100, msec, 50, velocityUnits::pct);
  spinRoller(-1, rollerColor, 165);

  turnToAngle(0.1, 100, 500, 0.25);
}
