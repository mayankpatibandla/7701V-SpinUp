#include "gui.h"

vex::thread guiThread;

void guiInit() { guiThread = vex::thread(updateScreen); }

void updateScreen() {
  Brain.Screen.clearScreen();
  Brain.Screen.render();
  while (true) {
    Brain.Screen.clearScreen();

    drawField();
    printOdom();

    drawRobot();

    Brain.Screen.render();
    this_thread::sleep_for(50);
  }
}