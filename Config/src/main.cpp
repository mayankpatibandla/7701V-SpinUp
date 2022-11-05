#include "config-graphics-core.h"

vector<MultiButton> mainMenuButtons = {
  {
    0, 0, 120, 120, 5, 0,
    {"Red", "Blue", "Skills", "Test", "None"},
    {color(255, 255, 255), color(255, 255, 255), color(255, 255, 255), color(255, 255, 255), color(255, 255, 255)},
    {color(255, 0, 0), color(0, 0, 255), color(27, 62, 89), color(7, 94, 7), color(28, 27, 3)},
    mono20
  },
  {
    120, 0, 120, 120, 2, 0, 
    {"Left", "Right"},
    {color(255, 255, 255), color(255, 255, 255)},
    {color(66, 15, 23), color(10, 76, 84)},
    mono20
  },
  {
    240, 0, 120, 120, 2, 0, 
    {"Roller", "High Goal"},
    {color(255, 255, 255), color(255, 255, 255)},
    {color(66, 15, 23), color(10, 76, 84)},
    mono20
  },
  {
    360, 0, 120, 120, 2, 0, 
    {"Main", "Other"},
    {color(255, 255, 255), color(255, 255, 255)},
    {color(66, 15, 23), color(10, 76, 84)},
    mono20
  },
  {
    0, 120, 120, 120, 1, 0,
    {"SAVE [X]"},
    {color(255, 255, 255)},
    {color(10, 61, 35)},
    mono20
  }
};

int main() {
  if (!Brain.SDcard.isInserted()) {
    Brain.Screen.setFont(mono60);
    Brain.Screen.printAt(0, 60, "No SD Card!");
    Brain.Screen.setFont(mono20);
    while (!Brain.SDcard.isInserted())
      Controller.rumble("-.");
  }

  ifstream ifs;
  ifs.open("config/color.txt");
  ifs >> autonSelectMenu.multiButtons[0].state;
  ifs.close();
  ifs.open("config/side.txt");
  ifs >> autonSelectMenu.multiButtons[1].state;
  ifs.close();
  ifs.open("config/version.txt");
  ifs >> autonSelectMenu.multiButtons[2].state;
  ifs.close();
  ifs.open("config/type.txt");
  ifs >> autonSelectMenu.multiButtons[3].state;
  ifs.close();

  Menu &currentMenu = autonSelectMenu;
  currentMenu.setCurrentSelection(0);
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
