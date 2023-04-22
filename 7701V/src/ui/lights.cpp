#include "ui/lights.hpp"

vex::thread lightsThread;

void lightsInit() { lightsThread = vex::thread(lightsCore); }

// https://stackoverflow.com/a/40639903/10139506
uint32_t generateRainbow(double ratio) {
  // we want to normalize ratio so that it fits in to 6 regions
  // where each region is 256 units long
  int normalized = int(ratio * 256 * 6);

  // find the region for this position
  int region = normalized / 256;

  // find the distance to the start of the closest region
  int x = normalized % 256;

  uint8_t r = 0, g = 0, b = 0;
  switch (region) {
  case 0:
    r = 255;
    g = 0;
    b = 0;
    g += x;
    break;
  case 1:
    r = 255;
    g = 255;
    b = 0;
    r -= x;
    break;
  case 2:
    r = 0;
    g = 255;
    b = 0;
    b += x;
    break;
  case 3:
    r = 0;
    g = 255;
    b = 255;
    g -= x;
    break;
  case 4:
    r = 0;
    g = 0;
    b = 255;
    r += x;
    break;
  case 5:
    r = 255;
    g = 0;
    b = 255;
    b -= x;
    break;
  }
  return r + (g << 8) + (b << 16);
}

void lightsCore() {
  lights frontLights(22, 8, 64);
  frontLights.clear();

  frontLights.setBaseColor(selectedAuton.allianceColor == RED      ? 0xFF0000
                           : selectedAuton.allianceColor == BLUE   ? 0x0000FF
                           : selectedAuton.allianceColor == SKILLS ? 0x00FF00
                           : selectedAuton.allianceColor == TEST   ? 0xFFFF00
                           : selectedAuton.allianceColor == NONE   ? 0xFF00FF
                                                                   : 0x00FFFF);

  std::vector<uint32_t> rainbow;
  const int rainbowSize = 96;
  rainbow.reserve(rainbowSize);
  for (double i = 0; i < rainbowSize; i++) {
    uint32_t color = generateRainbow(i / rainbowSize);
    rainbow.push_back(color);
  }

  // Calibrating Inertial
  frontLights.loadingBar(frontLights.getBaseColor(), 2000.0);
  waitUntil(!frontLights.loadingBarArgs.isEnabled && !Inertial.isCalibrating());

  // frontLights.set_buffer(rainbow);
  frontLights.cycle(rainbow, 15);

  while (true) {
    // frontLights.pulse(0xFFFFFF, 8, 10, 0, false);
    // waitUntil(!frontLights.isPulsing());
    // this_thread::sleep_for(500);
    // frontLights.pulse(0xFFFFFF, 8, 10, 63, true);

    this_thread::sleep_for(100000);
  }
}
