#include "control/control.hpp"

void autons::leftHighGoal() {
  Flywheel.setTargetVelocity(0.875);
  angler.set(true);

  driveMtrs.spinFor(fwd, 100, msec, 50, velocityUnits::pct);
  spinRoller(-1, rollerColor, 200);

  turnToAngle(0.25, 100, 700, 0.5);

  this_thread::sleep_for(5000);

  Indexer.shootDisc();
  this_thread::sleep_for(2500);
  Indexer.shootDisc();

  this_thread::sleep_for(500);
  angler.set(false);
}