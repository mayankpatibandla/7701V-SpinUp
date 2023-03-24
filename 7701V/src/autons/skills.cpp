#include "auton-manager.h"
#include "control.h"

void autons::skills() {
  flyMtrs.spin(fwd, flywheelMatchLoadCoeff * 12, volt);
  intakeMtrs.spin(fwd, 12, volt);
  angler.set(true);
  this_thread::sleep_for(3000);

  // match loads 1
  matchLoadEnabled = true;
  this_thread::sleep_for(3000);

  // roller 1
  turnToAngle(-0.585, 100, 1500, 0.5, {0.8, 0, 0.1});
  intakeMtrs.stop();
  matchLoadEnabled = false;
  flyMtrs.spin(fwd, 12, volt);
  driveRelative(45, 200, 3500, 0.6);
  driveRelative(-6, 100, 800, 0.4);
  intakeMtrs.spin(fwd, 12, volt);
  this_thread::sleep_for(500);
  driveRelative(45, 100, 10000, 0.3);
  driveRelative(-20, 50, 800, 0.65);
  turnToAngle(0.05, 75, 600, 0.4, {0.9, 0, 0.0075});
  driveMtrs.spin(fwd, 0.45 * 12, volt);
  this_thread::sleep_for(800);
  driveMtrs.stop();
  driveRelative(-3, 0, 200);
  this_thread::sleep_for(2000);
  intakeMtrs.stop();
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(150);
  spinRoller(-1, rollerColor, 3, 2500);
  driveMtrs.stop();

  // roller 2
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(-16.25, 200, 1500, 0.5);
  turnToAngle(1.05, 75, 1500, 0.65, {0.9, 0, 0.0075});
  driveMtrs.spin(fwd, 0.45 * 12, volt);
  this_thread::sleep_for(800);
  driveMtrs.stop();
  driveRelative(-2.5, 0, 500);
  this_thread::sleep_for(750);
  intakeMtrs.stop();
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(150);
  spinRoller(-1, rollerColor, 3, 2500);
  driveMtrs.stop();

  // shoot discs
  flyMtrs.spin(fwd, 0.76 * 12, volt);
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(-7.5, 100, 1000);
  angler.set(false);
  turnToAngle(-0.1, 100, 2500, 0.4, {0.5, 0, 0.005});
  driveRelative(-63.75, 100, 3000, 0.6, {0.001, 0.000001, 0.000075});
  turnToAngle(0.25, 0, 1000, 0.5, {0.85, 0, 0.01});
  for (int i = 0; i < 3; i++) {
    if (!(storageDistMin < storageDistance.objectDistance(mm) &&
          storageDistance.objectDistance(mm) < storageDistMax)) {
      break;
    }

    Indexer.shootDisc();

    if (i == 2) {
      break;
    }

    this_thread::sleep_for(250 + i * 75);
  }

  // roller 3
  driveRelative(-45, 200, 3000, 0.45);
  driveRelative(1.5, 0, 200, 0.5);
  turnToAngle(-1.39, 100, 1000, 0.4);
  driveRelative(105, 300, 7500, 0.85, {0.0003, 0.00000005, 0.000025});
  turnToAngle(3.14, 100, 1000, 0.5);
  driveRelative(12, 150, 600);
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(150);
  spinRoller(-1, rollerColor, 3, 2500);
  driveMtrs.stop();

  // roller 4
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(-16.25, 200, 1500, 0.5);
  turnToAngle(-1.35, 75, 1500, 0.65, {0.9, 0, 0.0075});
  driveMtrs.spin(fwd, 0.45 * 12, volt);
  this_thread::sleep_for(800);
  driveMtrs.stop();
  driveRelative(-2.5, 0, 500);
  this_thread::sleep_for(1000);
  intakeMtrs.stop();
  turnToAngle(-1.35, 75, 1500, 0.65, {0.9, 0, 0.0075});
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(150);
  spinRoller(-1, rollerColor, 3, 2500);
  driveMtrs.stop();

  // endgame
  driveRelative(-12, 100, 1000);
  turnToAngle(-2.25, 100, 1500, 0.5);
  if (Competition.isCompetitionSwitch() || Competition.isFieldControl()) {
    expand();
  }
  driveRelative(12, 100, 1000, 0.5);
}