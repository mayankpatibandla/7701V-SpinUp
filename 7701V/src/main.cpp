#include "config/auton-manager.hpp"
#include "driver/driver.hpp"
#include "ui/debug.hpp"
#include "ui/gui.hpp"
#include "ui/lights.hpp"

int main() {
  sylib::initialize();
  devicesListInit();
  devicesInit();
  autonInit();
  driverInit();
  odomInit();
  debugInit();
  guiInit();
  lightsInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);
}