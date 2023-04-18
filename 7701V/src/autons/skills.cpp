#include "config/auton-manager.hpp"
#include "control/control.hpp"

void autons::skills() {
  flyMtrs.spin(fwd, flywheelMatchLoadCoeff * 12, volt);
  intakeMtrs.spin(fwd, 12, volt);
  angler.set(true);
  this_thread::sleep_for(3500);

  // match loads 1
  matchLoadEnabled = true;
  this_thread::sleep_for(11000);

  // roller 1
  turnToAngle(-0.66, 100, 1500, 0.5, {0.8, 0, 0.1});
  intakeMtrs.stop();
  matchLoadEnabled = false;
  flyMtrs.spin(fwd, 10, volt);
  driveRelative(45, 200, 3500, 0.6);
  driveRelative(-6, 100, 800, 0.4);
  intakeMtrs.spin(fwd, 12, volt);
  this_thread::sleep_for(500);
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(2000);
  driveMtrs.stop();
  this_thread::sleep_for(200);
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(2000);
  turnToAngle(-1.2, 100, 800, 0.5, {0.8, 0, 0.1});
  driveRelative(-14, 50, 1600, 0.65);
  turnToAngle(-0.05, 75, 600, 0.4, {0.9, 0, 0.0075});
  driveMtrs.spin(fwd, 0.45 * 12, volt);
  this_thread::sleep_for(800);
  intakeMtrs.stop();
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(150);
  spinRoller(-1, rollerColor, 3, 2500);
  driveMtrs.stop();
  Indexer.shootDisc();

  // roller 2
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(-18.5, 200, 1500, 0.5);
  turnToAngle(1.25, 75, 1500, 0.65, {0.9, 0, 0.0075});
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
  flyMtrs.spin(fwd, 0.6 * 12, volt);
  turnToAngle(-0.7, 100, 1500, 0.65, {0.9, 0, 0.0075});
  driveRelative(50, 100, 2500, 0.6);
  turnToAngle(-1.58, 100, 1500, 0.65, {0.9, 0, 0.0075});
  driveRelative(50, 100, 2000, 0.5);
  turnToAngle(-1.57, 100, 1500, 0.65, {0.9, 0, 0.0075});
  driveMtrs.spin(fwd, 0.6 * 12, volt);
  this_thread::sleep_for(2300);
  driveRelative(-1, 0, 250, 0.5);
  turnToAngle(-2.86, 100, 1500, 0.65, {0.9, 0, 0.0075});
  driveRelative(35, 100, 1200, 0.5);
  turnToAngle(-2.89, 100, 1500, 0.65, {0.9, 0, 0.0075});
  for (int i = 0; i < 3; i++) {
    if (!(storageDistMin < storageDistance.objectDistance(mm) &&
          storageDistance.objectDistance(mm) < storageDistMax)) {
      break;
    }

    Indexer.shootDisc();

    if (i == 2) {
      break;
    }

    this_thread::sleep_for(250 + i * 125);
  }

  // roller 3
  turnToAngle(3.12, 100, 1000, 0.65, {0.9, 0, 0.0075});
  intakeMtrs.spin(fwd, 12, volt);
  driveRelative(70, 100, 2500, 0.65);
  turnToAngle(-1.15, 100, 1500, 0.65, {0.9, 0, 0.0075});
  driveMtrs.spin(fwd, 0.45 * 12, volt);
  this_thread::sleep_for(150);
  intakeMtrs.stop();
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(150);
  spinRoller(-1, rollerColor, 3, 2500);
  driveMtrs.stop();

  // roller 4
  driveRelative(-22.25, 100, 1800, 0.65);
  turnToAngle(-2.95, 100, 1000, 0.65, {0.9, 0, 0.0075});
  driveMtrs.spin(fwd, 0.45 * 12, volt);
  this_thread::sleep_for(150);
  intakeMtrs.stop();
  driveMtrs.spin(fwd, 0.15 * 12, volt);
  this_thread::sleep_for(150);
  spinRoller(-1, rollerColor, 3, 2500);
  driveMtrs.stop();

  // endgame
  driveRelative(-12, 100, 1000);
  turnToAngle(-2.4, 100, 1500, 0.5);
  if (Competition.isCompetitionSwitch() || Competition.isFieldControl()) {
    expandAll();
  }
  driveRelative(12, 100, 1000, 0.5);
}