#include "auton-manager.h"
#include "control.h"

void autons::test() {
  // intakeMtrs.spin(fwd, -12, volt);
  // waitUntil(rollerOptical.color() == red);
  // intakeMtrs.stop();
  spinRoller(-1, rollerColor, 165);
}