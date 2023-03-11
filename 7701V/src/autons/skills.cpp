#include "auton-manager.h"
#include "control.h"

void autons::skills() {
  flyMtrs.spin(fwd, 0.85 * 12, volt);
  angler.set(true);
  this_thread::sleep_for(2500);

  // match loads 1
  matchLoadEnabled = true;
  this_thread::sleep_for(12500);
  matchLoadEnabled = false;

  // roller 1
  turnToAngle(-0.725, 100, 1500, 0.5, {0.8, 0, 0.1});
  driveRelative(60, 200, 1500, 0.8);
  turnToAngle(0.175, 75, 600, 0.4, {0.9, 0, 0.0075});
  driveRelative(15, 150, 600);
  spinRoller(-1, rollerColor, 165);

  // roller 2
  driveRelative(-15, 200, 1500, 0.5);
  turnToAngle(1.35, 75, 1500, 0.65, {0.9, 0, 0.0075});
  driveRelative(24, 150, 1200, 0.65);
  spinRoller(-1, rollerColor, 165);

  // endgame
  driveRelative(-12, 100, 1000);
  turnToAngle(-0.7, 100, 1500, 0.5);
  // expand();
}