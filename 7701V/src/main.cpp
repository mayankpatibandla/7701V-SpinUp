#include "auton-manager.h"
#include "debug.h"
#include "driver.h"
#include "gui.h"

int main() {
  devicesListInit();
  devicesInit();
  autonInit();
  driverInit();
  odomInit();
  debugInit();
  guiInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);
}