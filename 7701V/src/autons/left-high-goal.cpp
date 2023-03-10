#include "auton-manager.h"
#include "control.h"

void autons::leftHighGoal() {
  flyMtrs.spin(fwd, .85 * 12, volt);
  angler.set(true);

  driveMtrs.spinFor(fwd, 100, msec, 50, velocityUnits::pct);
  spinRoller(-1, rollerColor, 165);

  turnToAngle(0.35, 100, 700, 0.5);

  this_thread::sleep_for(3500);

  Indexer.shootDisc();
  this_thread::sleep_for(1500);
  Indexer.shootDisc();

  this_thread::sleep_for(500);
  angler.set(false);
}