#include "config/auton-manager.hpp"
#include "driver/driver.hpp"
#include "ui/debug.hpp"
#include "ui/gui.hpp"
#include "ui/lights.hpp"

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