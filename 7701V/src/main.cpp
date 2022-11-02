#include "auton-manager.h"
#include "driver.h"

int main() {
  devicesInit();
  driverInit();
  odomInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);

  while (true) {
    this_thread::sleep_for(0xFFFFFFFF);
  }
}