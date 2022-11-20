#include "auton-manager.h"

void autons::test() {
  // turnToAngle(M_PI_2, 1250, 1600, {3.5, 0, 0.4});
  // driveRelative(24, 1000, 2000, {.0025, 0.000001, 0.00015});
  // turnToAngle(atan2(118, -11) + M_PI);
  turnToAngle(atan2(pt::y(), pt::x()) + M_PI, 0, 2000);
}