#include "auton-manager.h"
#include "control.h"

void autons::skills() {
  flyMtrs.spin(fwd, flywheelMatchLoadCoeff * 12, volt);
  angler.set(true);
  this_thread::sleep_for(4000);

  // match loads 1
  matchLoadEnabled = true;
  this_thread::sleep_for(10000);
  matchLoadEnabled = false;

  // roller 1
  turnToAngle(-0.8, 100, 1500, 0.5, {0.8, 0, 0.1});
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(60, 200, 1500, 0.8);
  turnToAngle(0.175, 75, 600, 0.4, {0.9, 0, 0.0075});
  driveRelative(36, 150, 3000);
  spinRoller(-1, rollerColor, 190);

  // roller 2
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(-17, 200, 1500, 0.5);
  turnToAngle(1.35, 75, 1500, 0.65, {0.9, 0, 0.0075});
  intakeMtrs.stop();
  Indexer.shootDisc();
  driveRelative(40, 150, 1200, 0.65);
  Indexer.shootDisc();
  this_thread::sleep_for(1000);
  spinRoller(-1, rollerColor, 190);

  // endgame
  driveRelative(-12, 100, 1000);
  turnToAngle(0.75, 100, 1500, 0.5);
  if (Competition.isCompetitionSwitch() || Competition.isFieldControl()) {
    expand();
  }
}