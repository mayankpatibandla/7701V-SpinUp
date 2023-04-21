#include "config/auton-manager.hpp"
#include "driver/driver.hpp"
#include "ui/ui.hpp"

int main() {
  sylib::initialize();
  autonInit();
  lightsInit();
  devicesListInit();
  devicesInit();
  odomInit();
  debugInit();
  guiInit();
  driverInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);
}