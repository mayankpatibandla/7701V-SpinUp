#include "ui/lights.hpp"
#include "driver/driver.hpp"

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
  frontLights.flash(0xFFFFFF, 250);
  waitUntil(!frontLights.flashArgs.isEnabled);

  // Pre field control
  while (!Competition.isCompetitionSwitch() && !Competition.isFieldControl()) {
    if (!frontLights.bounceArgs.isEnabled) {
      frontLights.bounce(0, 250, 6, 13);
    }

    if (Indexer.value() && !frontLights.isPulsing()) {
      frontLights.pulse(0xFFFF00, 12, 100);
      waitUntil(!Indexer.value() && !frontLights.isPulsing());
    }

    this_thread::sleep_for(10);
  }

  // Pre auton disabled
  while (!Competition.isEnabled()) {
    if (!frontLights.bounceArgs.isEnabled) {
      frontLights.bounce(0xFFFFFF, 250, 6, 13);
    }

    if (Indexer.value() && !frontLights.isPulsing()) {
      frontLights.pulse(0xFFFF00, 12, 100);
      waitUntil(!Indexer.value() && !frontLights.isPulsing());
    }

    this_thread::sleep_for(10);
  }

  // Auton
  while (Competition.isEnabled()) {
    for (int i = 0; i < frontLights.stripSize() / 2; i++) {
      frontLights.set_pixel(lights::hsv_to_rgb({leftRollerOptical.hue(), 1, 1}),
                            i);
    }
    for (int i = frontLights.stripSize() / 2; i < frontLights.stripSize();
         i++) {
      frontLights.set_pixel(
          lights::hsv_to_rgb({rightRollerOptical.hue(), 1, 1}), i);
    }

    if (Indexer.value() && !frontLights.isPulsing()) {
      frontLights.pulse(0xFFFF00, 12, 100);
      waitUntil(!Indexer.value() && !frontLights.isPulsing());
    }

    this_thread::sleep_for(10);
  }

  // Post auton disabled
  frontLights.set_all(frontLights.getBaseColor());
  while (!Competition.isEnabled()) {
    if (!frontLights.bounceArgs.isEnabled) {
      frontLights.bounce(0xFFFFFF, 250, 6, 13);
    }

    if (Indexer.value() && !frontLights.isPulsing()) {
      frontLights.pulse(0xFFFF00, 12, 100);
      waitUntil(!Indexer.value() && !frontLights.isPulsing());
    }

    this_thread::sleep_for(10);
  }

  // Driver
  int driverPhase = 0;
  timer driverTimer;
  driverTimer.reset();
  while (Competition.isEnabled()) {
    // First 45 seconds
    if (driverPhase == 0) {
      // https://uigradients.com/#KyooPal
      frontLights.gradient(0xDD3E54, 0x6BE585);
      frontLights.cycle(*frontLights, 8);
      driverPhase++;
    }
    // 1 min to 30 sec
    else if (driverTimer.time(sec) > 45 && driverPhase == 1) {
      // https://uigradients.com/#KyeMeh
      frontLights.gradient(0x8360C3, 0x2EBF91);
      frontLights.cycle(*frontLights, 16);
      driverPhase++;
    }
    // 30 sec to endgame
    else if (driverTimer.time(sec) > 75 && driverPhase == 2) {
      // https://uigradients.com/#CrystalClear
      frontLights.gradient(0x159957, 0x155799);
      frontLights.cycle(*frontLights, 32);
      driverPhase++;
    }
    // Endgame
    else if (driverTimer.time(sec) > 95 && driverPhase == 3) {
      frontLights.set_all(frontLights.getBaseColor());
      driverPhase++;
    } else if (driverPhase == 4 && !frontLights.flashArgs.isEnabled) {
      frontLights.flash(0, 200, true);
    }

    if (expansionActivated || driverTimer.time(sec) > 105) {
      break;
    }

    if (Indexer.value() && !frontLights.isPulsing()) {
      frontLights.pulse(0xFFFF00, 12, 100);
      waitUntil(!Indexer.value() && !frontLights.isPulsing());
    }

    this_thread::sleep_for(10);
  }

  // Endgame
  this_thread::sleep_for(100);
  frontLights.cycle(rainbow, 32);
  while (true) {
    if (Indexer.value() && !frontLights.isPulsing()) {
      frontLights.pulse(0xFFFF00, 12, 100);
      waitUntil(!Indexer.value() && !frontLights.isPulsing());
    }

    this_thread::sleep_for(10);
  }
}
