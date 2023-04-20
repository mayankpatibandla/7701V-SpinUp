#include "ui/lights.hpp"

vex::thread lightsThread;

void lightsInit() { lightsThread = vex::thread(lights); }

void lights() {
  sylib::Addrled addrleds = sylib::Addrled(22, 8, 64);
  addrleds.gradient(0xFF00FF, 0x00FF00);
  addrleds.cycle(*addrleds, 15);

  while (true) {
    this_thread::sleep_for(0xFFFFFFFF);
  }
}
