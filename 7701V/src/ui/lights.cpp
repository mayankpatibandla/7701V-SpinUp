#include "ui/lights.hpp"

vex::thread lightsThread;

void lightsInit() { lightsThread = vex::thread(lightsCore); }

void lightsCore() {
  lights frontLights(22, 8, 64);
  frontLights.clear();

  frontLights.setBaseColor(selectedAuton.allianceColor == RED    ? 0xFF0000
                           : selectedAuton.allianceColor == BLUE ? 0x0000FF
                                                                 : 0x00FF00);

  frontLights.loadingBar(frontLights.getBaseColor(), 2000.0);
  this_thread::sleep_for(10000);

  while (true) {
    frontLights.pulse(0xFFFFFF, 2, 15);
    this_thread::sleep_for(2500);
    this_thread::sleep_for(2500);
  }
}
