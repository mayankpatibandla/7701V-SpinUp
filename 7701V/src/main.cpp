#include "auton-manager.h"
#include "driver.h"
#include "debug.h"

int main() {
  devicesInit();
  autonInit();
  driverInit();
  odomInit();
  debugInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);

  while (true) {
    this_thread::sleep_for(0xFFFFFFFF);
  }
}