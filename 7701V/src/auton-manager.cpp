#include "auton-manager.h"

// init auton configs with default values, will be overridden
teamColor tc = RED;
teamSide ts = LEFT;
autonVersion av = ROLLER;
autonType at = MAIN;

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
    selectedAuton = {auton_skills};
  } break;
  case TEST: {
    selectedAuton = {auton_test};
  } break;
  case NONE: {
    // no auton
  } break;
  default: {
    // invalid input
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
          selectedAuton = {auton_leftRoller};
        } break;
        case OTHER: { // other
          // undefined
        } break;
        }
      } break;
      case HIGH_GOAL: { // high goal
        switch (at) {
        case MAIN: { // main
          selectedAuton = {auton_leftHighGoal};
        } break;
        case OTHER: { // other
          // undefined
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
          selectedAuton = {auton_rightRoller};
        } break;
        case OTHER: { // other
          // undefined
        } break;
        }
      } break;
      case HIGH_GOAL: { // neutral
        switch (at) {
        case MAIN: { // main
          // undefined
        } break;
        case OTHER: { // other
          // undefined
        } break;
        }
      } break;
      }
    } break;
    }
  }
}

void auton() {
  selectedAuton.autonCallback();
}