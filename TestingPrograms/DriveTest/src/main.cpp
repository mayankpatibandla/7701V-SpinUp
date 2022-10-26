#include "driver.h"

using namespace vex;

void auton() {}

int main() {
  lbDriveMtr.setBrake(brake);
  ltDriveMtr.setBrake(brake);
  rbDriveMtr.setBrake(brake);
  rtDriveMtr.setBrake(brake);

  lFlyMtr.setBrake(coast);
  rFlyMtr.setBrake(coast);

  Controller.ButtonX.pressed([]() { flyMtrs.toggleState(); });

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);
}
