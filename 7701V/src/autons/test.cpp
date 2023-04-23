#include "control/control.hpp"

void autons::test() {
  PID testPID = {0.001, 0, 0, 6};
  driveRelative(48, 0, 2000, 1, testPID);
  this_thread::sleep_for(1000);
  std::cout << "X (in): " << pt::x() << " Y(in): " << pt::x() << std::endl;
  driveRelative(-48, 0, 2000, 1, testPID);
  this_thread::sleep_for(1000);
  std::cout << "X (in): " << pt::x() << " Y(in): " << pt::x() << std::endl;
}