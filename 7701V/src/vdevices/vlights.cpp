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
  std::cout << "lights thread started" << std::endl;

  while (true) {
    instance->loadingBar_i();
    this_thread::sleep_for(10);
  }
}

uint32_t vdevices::lights::getBaseColor() { return baseColor; }
void vdevices::lights::setBaseColor(uint32_t color) { baseColor = color; }

void vdevices::lights::loadingBar_i() {
  if (loadingBarArgs.isEnabled) {
    std::cout << "loading bar enabled" << std::endl;
    if (loadingBarArgs.endPos == -1) {
      loadingBarArgs.endPos = strip_length - 1;
    }

    for (int i = loadingBarArgs.startPos; i <= loadingBarArgs.endPos; i++) {
      std::cout << "loading bar loop" << std::endl;
      std::cout << "loading bar color = " << (int)loadingBarArgs.color
                << std::endl;
      set_pixel(loadingBarArgs.color, i);
      std::cout << "loading bar set pixel" << std::endl;
      std::cout << "loading bar delay time = " << (int)loadingBarArgs.time
                << " / " << (int)strip_length << std::endl;
      this_thread::sleep_for(loadingBarArgs.time / strip_length);
    }
    std::cout << "loading bar exit loop" << std::endl;
    loadingBarArgs.isEnabled = false;
    std::cout << "loading bar disabled" << std::endl;
  }
}

void vdevices::lights::loadingBar(uint32_t color, double time, int startPos,
                                  int endPos) {
  std::cout << "loading bar called" << std::endl;

  loadingBarArgs = loadingBarArgs_t(color, time, startPos, endPos, true);
}
