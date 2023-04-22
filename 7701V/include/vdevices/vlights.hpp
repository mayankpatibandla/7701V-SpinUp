#pragma once
#include "sylib/sylib.hpp"

namespace vdevices {
class lights : public sylib::Addrled {
protected:
  uint32_t baseColor;

  vex::thread lightsThread;
  static void lightsCore(void *arg);

  struct loadingBarArgs_t {
    uint32_t color;
    double time;
    int startPos = 0;
    int endPos = -1;
    bool isEnabled = false;

    loadingBarArgs_t(uint32_t color = 0, double time = 0, int startPos = 0,
                     int endPos = -1, bool isEnabled = false)
        : color(color), time(time), startPos(startPos), endPos(endPos),
          isEnabled(isEnabled) {}
  };
  void loadingBar_i();

public:
  lights(
      const std::uint8_t smart_port, const std::uint8_t adi_port,
      const std::uint8_t strip_length,
      const std::vector<std::uint32_t> colors = std::vector<std::uint32_t>());

  uint32_t getBaseColor();
  void setBaseColor(uint32_t color);

  bool isPulsing();
  const uint8_t stripSize();

  loadingBarArgs_t loadingBarArgs;
  void loadingBar(uint32_t color, double time, int startPos = 0,
                  int endPos = -1);
};
} // namespace vdevices