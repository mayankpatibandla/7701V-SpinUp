#include "auton-manager.h"
#include "control.h"

void autons::test() {
  // spinRoller(-1, rollerColor, 165);

  flyMtrs.spin(fwd, 0.825 * 12, volt);
  matchLoadEnabled = true;
  waitUntil(Controller.ButtonB.pressing());
}