#include "config-graphics-core.h"

int main() {
  if (!Brain.SDcard.isInserted()) {
    Brain.Screen.setFont(mono60);
    Brain.Screen.printAt(0, 60, "No SD Card!");
    Brain.Screen.setFont(mono20);
    while (!Brain.SDcard.isInserted())
      Controller.rumble("-.");
  }

  Menu &currentMenu = autonSelectMenu;
  currentMenu.setCurrentSelection(0);

  ifstream ifs;
  ifs.open("config/color.txt");
  ifs >> currentMenu.multiButtons[0].state;
  ifs.close();
  ifs.open("config/side.txt");
  ifs >> currentMenu.multiButtons[1].state;
  ifs.close();
  ifs.open("config/version.txt");
  ifs >> currentMenu.multiButtons[2].state;
  ifs.close();
  ifs.open("config/type.txt");
  ifs >> currentMenu.multiButtons[3].state;
  ifs.close();

  
  Brain.Screen.render();
  while (true) {
    int waitTime = 250;
    Brain.Screen.clearScreen();
    drawMenu(currentMenu);
    switch (useMenu(currentMenu)) {
      if (currentMenu.id == 0) {
      case 1: { // select button
        switch (currentMenu.getCurrentSelection()) {
        case 0: {
          currentMenu.multiButtons[0].setState(
              currentMenu.multiButtons[0].state + 1);
        } break;
        case 1: {
          currentMenu.multiButtons[1].setState(
              currentMenu.multiButtons[1].state + 1);
        } break;
        case 2: {
          currentMenu.multiButtons[2].setState(
              currentMenu.multiButtons[2].state + 1);
        } break;
        case 3: {
          currentMenu.multiButtons[3].setState(
              currentMenu.multiButtons[3].state + 1);
        } break;
        case 4: {
          saveFiles();
        } break;
        default: {
          waitTime = 5;
        } break;
        }
      } break;
      case -1: { // back
      } break;
      case 2: { // save
        saveFiles();
      } break;
      }
    }
    Brain.Screen.render();
    wait(waitTime, msec);
  }
  return 0;
}
