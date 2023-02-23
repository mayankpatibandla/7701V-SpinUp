#include "auton-manager.h"

void autons::test() {
  intakeMtrs.spin(fwd, -12, volt);
  waitUntil(rollerOptical.color() == red);
  intakeMtrs.stop();
}