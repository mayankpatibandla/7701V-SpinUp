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
    setAuton(auton_skills, tc);
  } break;
  case TEST: {
    setAuton(auton_test, tc);
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
          setAuton(auton_leftRoller, tc);
        } break;
        case OTHER: { // other
          // undefined
        } break;
        }
      } break;
      case HIGH_GOAL: { // high goal
        switch (at) {
        case MAIN: { // main
          setAuton(auton_leftHighGoal, tc);
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
          setAuton(auton_rightRoller, tc);
        } break;
        case OTHER: { // other
          // undefined
        } break;
        }
      } break;
      case HIGH_GOAL: { // neutral
        switch (at) {
        case MAIN: { // main
          setAuton(auton_rightHighGoal, tc);
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

void setAuton(void (*callback)(void), teamColor allianceColor) {
  selectedAuton = {callback, allianceColor};
}

void auton() {
  flyMtrs.spin(fwd, 12, volt);

  intakeMtrs.spin(fwd, -12, volt);
  driveMtrs.spinFor(90, deg, 50, velocityUnits::pct);
  this_thread::sleep_for(197);
  intakeMtrs.stop(brake);

  driveMtrs.spinFor(-100, deg, 50, velocityUnits::pct);

  leftDriveMtrs.spin(fwd, -3, volt);
  rightDriveMtrs.spin(fwd, 3, volt);

  waitUntil(Inertial.heading() > 20);
  driveMtrs.stop();
  this_thread::sleep_for(3500);
  Indexer.shootDisc();
  this_thread::sleep_for(2000);
  Indexer.shootDisc();
  this_thread::sleep_for(2000);
}

void auton_skills() {}
void auton_test() {}

void auton_leftRoller() {}
void auton_leftHighGoal() {}

void auton_rightRoller() {}
void auton_rightHighGoal() {}