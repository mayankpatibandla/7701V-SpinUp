#include "config/auton-manager.hpp"
#include "control/control.hpp"

void autons::test() {
  // turnToAngle(M_PI, 0, 0, 1, {10, 0, 0});
  Flywheel.setTargetVelocity(0.8);
  waitUntil(Controller.ButtonLeft.pressing());
}