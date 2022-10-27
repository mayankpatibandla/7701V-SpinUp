#include "auton-manager.h"
#include "driver.h"

int main() {
  devicesInit();
  driverInit();

  Competition.drivercontrol(driver);
  Competition.autonomous(auton);

  std::cout << flyMtrs.count() << ", " << driveMtrs.count() << ", " << intakeMtrs.count() << std::endl;

  while(true){
    this_thread::sleep_for(0xFFFFFFFF);
  }
}