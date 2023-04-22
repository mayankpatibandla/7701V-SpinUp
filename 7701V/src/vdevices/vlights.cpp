#include "vdevices/vlights.hpp"

vdevices::lights::lights(const std::uint8_t smart_port,
                         const std::uint8_t adi_port,
                         const std::uint8_t strip_length,
                         const std::vector<std::uint32_t> colors)
    : sylib::Addrled(smart_port, adi_port, strip_length, colors) {
  lightsThread = vex::thread(lightsCore, static_cast<void *>(this));
}

void vdevices::lights::lightsCore(void *arg) {
  if (arg == NULL) {
    return;
  }
  lights *instance = static_cast<lights *>(arg);

  while (true) {
    instance->loadingBar_i();
    this_thread::sleep_for(10);
  }
}

uint32_t vdevices::lights::getBaseColor() { return baseColor; }
void vdevices::lights::setBaseColor(uint32_t color) { baseColor = color; }

bool vdevices::lights::isPulsing() { return sendingPulse; }

const uint8_t vdevices::lights::stripSize() { return strip_length; }

void vdevices::lights::loadingBar_i() {
  if (loadingBarArgs.isEnabled) {
    if (loadingBarArgs.endPos == -1) {
      loadingBarArgs.endPos = strip_length - 1;
    }

    for (int i = loadingBarArgs.startPos; i <= loadingBarArgs.endPos; i++) {
      set_pixel(loadingBarArgs.color, i);
      this_thread::sleep_for(loadingBarArgs.time / strip_length);
    }

    loadingBarArgs.isEnabled = false;
  }
}

void vdevices::lights::loadingBar(uint32_t color, double time, int startPos,
                                  int endPos) {
  loadingBarArgs = loadingBarArgs_t(color, time, startPos, endPos, true);
}
