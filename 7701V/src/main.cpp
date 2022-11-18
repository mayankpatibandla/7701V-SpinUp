#include "auton-manager.h"
#include "debug.h"
#include "driver.h"
#include "gui.h"

int main() {
  devicesInit();
  autonInit();
  driverInit();
  odomInit();
  debugInit();
  guiInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);

  while (true) {
    this_thread::sleep_for(0xFFFFFFFF);
  }
}