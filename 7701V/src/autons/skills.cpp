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
  turnToAngle(-0.7, 100, 1500, 0.5, {0.8, 0, 0.1});
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(50, 200, 3500, 0.4);
  turnToAngle(0.175, 75, 600, 0.4, {0.9, 0, 0.0075});
  driveRelative(36, 150, 1100, 0.6);
  driveMtrs.spin(fwd, 10, pct);
  spinRoller(-1, rollerColor, 250, 5000);
  driveMtrs.stop();

  // roller 2
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(-17, 200, 1500, 0.5);
  turnToAngle(1.35, 75, 1500, 0.65, {0.9, 0, 0.0075});
  intakeMtrs.stop();
  driveRelative(40, 150, 1200, 0.65);
  this_thread::sleep_for(1000);
  driveMtrs.spin(fwd, 10, pct);
  spinRoller(-1, rollerColor, 250, 5000);
  driveMtrs.stop();

  // intake disc
  driveRelative(-12, 100, 1000);
  turnToAngle(0.75, 100, 1500, 0.5);
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(18, 200, 1500, 0.4);
  driveRelative(-7, 100, 700, 0.4);

  // shoot discs
  angler.set(false);
  turnToAngle(0, 100, 2000, 0.5, {0.9, 0, 0.01});
  driveRelative(-80, 100, 3000, 1, {0.001, 0.000001, 0.000075});
  turnToAngle(0.25, 0, 1000, 0.5, {0.85, 0, 0.01});
  Indexer.shootDisc();
  this_thread::sleep_for(200);
  Indexer.shootDisc();

  // endgame
  if (Competition.isCompetitionSwitch() || Competition.isFieldControl()) {
    expand();
  }
}