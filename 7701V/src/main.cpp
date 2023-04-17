#include "auton-manager.h"
#include "debug.h"
#include "driver.h"
#include "gui.h"
#include "sylib/sylib.hpp"

int main() {
  devicesListInit();
  devicesInit();
  autonInit();
  driverInit();
  odomInit();
  debugInit();
  guiInit();

  sylib::Addrled testLights(22, 7, 64);
  testLights.gradient(0x00FF00, 0x0000FF);

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);
}