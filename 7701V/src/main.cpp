#include "driver.h"
#include "auton-manager.h"

int main() {
  lbDriveMtr.setBrake(brake);
  ltDriveMtr.setBrake(brake);
  rbDriveMtr.setBrake(brake);
  rtDriveMtr.setBrake(brake);

  lFlyMtr.setBrake(coast);
  rFlyMtr.setBrake(coast);

  driverInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);
}
