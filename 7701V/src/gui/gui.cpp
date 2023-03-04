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
    printOptical();
    drawRobot({120, 120, 0});

    Brain.Screen.setFillColor(transparent);
    Brain.Screen.setPenColor(white);
    Brain.Screen.printAt(240, 190, "Distance: %3f mm", storageDistance.objectDistance(mm));

    Brain.Screen.render();
    this_thread::sleep_for(50);
  }
}