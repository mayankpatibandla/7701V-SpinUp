#include "auton-manager.h"
#include "control.h"

void autons::skills() {
  flyMtrs.spin(fwd, 0.79 * 12, volt);
  angler.set(true);
  this_thread::sleep_for(2500);

  // starting match loads
  matchLoadEnabled = true;
  this_thread::sleep_for(12500);

  // roller
  turnToAngle(-0.4, 100, 1500, 0.5, {0.8, 0, 0.1});
  driveRelative(36, 200, 1200);
  turnToAngle(-M_PI_2, 75, 1000, 0.75);
  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165);
}