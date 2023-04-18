#include "auton-manager.hpp"
#include "control.hpp"

void autons::rightHighGoal() {
  flyMtrs.spin(fwd, 0.91 * 12, volt);
  angler.set(true);

  // roller
  driveRelative(21, 300, 1700);
  turnToAngle(-M_PI_2 + 0.1, 600, 1200);

  driveRelative(12, 150, 600);
  spinRoller(-1, rollerColor, 165);

  driveRelative(-2.4166, 0, 1000);

  // shoot preloads
  turnToAngle(-1.62, 200, 700);
  this_thread::sleep_for(250);
  Indexer.shootDisc();
  this_thread::sleep_for(1600);
  Indexer.shootDisc();
  this_thread::sleep_for(250);

  // intake discs
  // 2.67, 2.46, -2.28
  intakeMtrs.spin(fwd, 12, volt);
  flyMtrs.spin(fwd, 0.785 * 12, volt);
  turnToAngle(2.65, 250, 1750, 0.5, {0.8, 0, 0.1});
  // driveRelative(80, 400, 2500, {0.0005, 0.000001, 0.000025});
  driveMtrs.spin(fwd, 6, volt);
  this_thread::sleep_for(1700); // 2150
  driveMtrs.stop();

  // shoot discs
  turnToAngle(-1.9, 300, 1500, 0.75, {0.6, 0, 0.0075}); //-2.325
  this_thread::sleep_for(500);
  // 111.25, 34 + 13/16
  // turnToAngle(M_PI + std::atan2((54+13/16) - pt::y(), 111.25 - pt::x()), 300,
  // 1500);
  Indexer.shootDisc();
  this_thread::sleep_for(1500);
  Indexer.shootDisc();
  this_thread::sleep_for(1500);
  Indexer.shootDisc();
  this_thread::sleep_for(1500);
  angler.set(false);
}