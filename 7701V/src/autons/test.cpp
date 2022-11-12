#include "auton-manager.h"

void autons::test() { 
  // turnToAngle(M_PI_2, 1250, 1600, {3.5, 0, 0.4}); 
  driveRelative(24, 1000, 2000, {.05, 0, 0});
  }