#include "auton-manager.h"

// init auton configs with default values, will be overridden
teamColor tc = RED;
teamSide ts = LEFT;
autonVersion av = ROLLER;
autonType at = MAIN;

color rollerColor = transparent;

auton_t selectedAuton;

void autonInit() {
  if (!Brain.SDcard.isInserted()) {
    Brain.Screen.setFont(mono60);
    Brain.Screen.printAt(0, 60, "No SD Card!");
    Brain.Screen.setFont(mono20);
    while (!Brain.SDcard.isInserted())
      Controller.rumble("-.");
  }

  std::ifstream ifs;
  int int_tc, int_ts, int_av, int_at;

  ifs.open("config/color.txt");
  ifs >> int_tc;
  ifs.close();
  ifs.open("config/side.txt");
  ifs >> int_ts;
  ifs.close();
  ifs.open("config/version.txt");
  ifs >> int_av;
  ifs.close();
  ifs.open("config/type.txt");
  ifs >> int_at;
  ifs.close();

  tc = static_cast<teamColor>(int_tc);
  ts = static_cast<teamSide>(int_ts);
  av = static_cast<autonVersion>(int_av);
  at = static_cast<autonType>(int_at);

  bool next = false;

  switch (tc) {
  case RED: {
    next = true;
  } break;
  case BLUE: {
    next = true;
  } break;
  case SKILLS: {
    selectedAuton = {autons::skills};
    Controller.Screen.print("Skills Auton");
  } break;
  case TEST: {
    selectedAuton = {autons::test};
    Controller.Screen.print("Test Auton");
  } break;
  case NONE: {
    // no auton
    Controller.Screen.print("No Auton");
  } break;
  default: {
    // invalid input
    Controller.Screen.print("Invalid Auton");
  } break;
  }

  // side
  if (next) {
    switch (ts) {
    case LEFT: { // left
      switch (av) {
      case ROLLER: { // roller
        switch (at) {
        case MAIN: { // main
          selectedAuton = {autons::leftRoller, tc};
          Controller.Screen.print("Left Roller");
        } break;
        case OTHER: { // other
          // undefined
          Controller.Screen.print("Undefined Auton");
        } break;
        }
      } break;
      case HIGH_GOAL: { // high goal
        switch (at) {
        case MAIN: { // main
          selectedAuton = {autons::leftHighGoal, tc};
          Controller.Screen.print("Left High Goal");
        } break;
        case OTHER: { // other
          Controller.Screen.print("Undefined Auton");
        } break;
        }
      } break;
      }
    } break;
    case RIGHT: { // right
      switch (av) {
      case ROLLER: { // roller
        switch (at) {
        case MAIN: { // main
          selectedAuton = {autons::rightRoller, tc};
          Controller.Screen.print("Right Roller");
        } break;
        case OTHER: { // other
          Controller.Screen.print("Undefined Auton");
        } break;
        }
      } break;
      case HIGH_GOAL: { // high goal
        switch (at) {
        case MAIN: { // main
          selectedAuton = {autons::rightHighGoal, tc};
          Controller.Screen.print("Right High Goal");
        } break;
        case OTHER: { // other
          Controller.Screen.print("Undefined Auton");
        } break;
        }
      } break;
      }
    } break;
    }
  }
}

void auton() { selectedAuton.autonCallback(); }