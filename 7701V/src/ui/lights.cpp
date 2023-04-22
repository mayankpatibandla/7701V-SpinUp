#include "ui/lights.hpp"

vex::thread lightsThread;

void lightsInit() { lightsThread = vex::thread(lights); }

void lights() {
  sylib::Addrled frontLights(22, 8, 64);
  frontLights.clear();

  uint32_t allianceColor = selectedAuton.allianceColor == RED    ? 0xFF0000
                           : selectedAuton.allianceColor == BLUE ? 0x0000FF
                                                                 : 0x00FF00;

  for (int i = 0; i < 64; i++) {
    frontLights.set_pixel(allianceColor, i);
    this_thread::sleep_for(2000 / 64);
  }

  while (true) {
    frontLights.pulse(0xFFFFFF, 2, 10);
    this_thread::sleep_for(2500);
  }
}
