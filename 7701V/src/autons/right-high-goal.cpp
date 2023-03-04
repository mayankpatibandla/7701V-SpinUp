#include "auton-manager.h"
#include "control.h"

void autons::rightHighGoal() {
  flyMtrs.spin(fwd, 0.9125 * 12, volt);

  // roller
  driveRelative(23, 300, 1700);
  turnToAngle(-M_PI_2 + 0.1, 600, 1200);

  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165);

  driveRelative(-2.4166, 0, 1000);

  // shoot preloads
  turnToAngle(-1.9375, 200, 700);
  this_thread::sleep_for(750);
  Indexer.shootDisc();
  this_thread::sleep_for(250);
  angler.set(true);
  this_thread::sleep_for(250);
  Indexer.shootDisc();
  this_thread::sleep_for(250);
  angler.set(false);

  // intake discs
  // 2.67, 2.46, -2.28
  intakeMtrs.spin(fwd, 12, volt);
  flyMtrs.spin(fwd, 0.85 * 12, volt);
  turnToAngle(2.815, 250, 1750);
  // driveRelative(80, 400, 2500, {0.0005, 0.000001, 0.000025});
  driveMtrs.spin(fwd, 6, volt);
  this_thread::sleep_for(2150);
  driveMtrs.stop();

  //shoot discs
  turnToAngle(-1.9125, 300, 1500, 1, {0.8, 0, 0.0075});//-2.325
  this_thread::sleep_for(100);
  // 111.25, 34 + 13/16
  // turnToAngle(M_PI + std::atan2((54+13/16) - pt::y(), 111.25 - pt::x()), 300, 1500);
  Indexer.shootDisc();
  this_thread::sleep_for(1000);
  Indexer.shootDisc();
  this_thread::sleep_for(1000);
  Indexer.shootDisc();
  this_thread::sleep_for(1000); 
}