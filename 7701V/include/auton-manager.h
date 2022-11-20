#pragma once
#include "control.h"

// config
enum teamColor { RED = 0, BLUE = 1, SKILLS = 2, TEST = 3, NONE = 4 };
enum teamSide { LEFT = 0, RIGHT = 1 };
enum autonVersion { ROLLER = 0, HIGH_GOAL = 1 };
enum autonType { MAIN = 0, OTHER = 1 };

struct auton_t {
  void (*autonCallback)(void);
  teamColor allianceColor;
  teamSide side;
  autonVersion version;
  autonType type;

  auton_t(void (*autonCallback)(void) = nullptr, teamColor allianceColor = NONE,
          teamSide side = LEFT, autonVersion version = ROLLER,
          autonType type = MAIN)
      : autonCallback(autonCallback), allianceColor(allianceColor), side(side),
        version(version), type(type) {}
};

extern void autonInit();
extern auton_t selectedAuton;
extern void auton();

// autons
namespace autons {
extern void skills();
extern void test();

extern void leftRoller();
extern void leftHighGoal();

extern void rightRoller();
extern void rightHighGoal();
} // namespace autons