#include "auton-manager.hpp"
#include "control.hpp"

void autons::leftHighGoal() {
  flyMtrs.spin(fwd, 0.915 * 12, volt);
  angler.set(true);

  driveMtrs.spinFor(fwd, 100, msec, 50, velocityUnits::pct);
  spinRoller(-1, rollerColor, 200);

  turnToAngle(0.35, 100, 700, 0.5);

  this_thread::sleep_for(3500);

  Indexer.shootDisc();
  flyMtrs.spin(fwd, 0.925 * 12, volt);
  this_thread::sleep_for(2500);
  Indexer.shootDisc();

  this_thread::sleep_for(500);
  angler.set(false);
}