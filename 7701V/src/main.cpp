#include "config/auton-manager.hpp"
#include "driver/driver.hpp"
#include "ui/debug.hpp"
#include "ui/gui.hpp"


int main() {
  devicesListInit();
  devicesInit();
  autonInit();
  driverInit();
  odomInit();
  debugInit();
  guiInit();
  sylib::initialize();

  sylib::Addrled testLights(22, 7, 64);
  testLights.gradient(0x00FF00, 0x0000FF);
  testLights.cycle(*testLights, 5);

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);
}