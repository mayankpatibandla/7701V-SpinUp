#pragma once
#include "control.h"

// config
enum teamColor { RED = 0, BLUE = 1, SKILLS = 2, TEST = 3, NONE = 4 };
enum teamSide { LEFT = 0, RIGHT = 1 };
enum autonVersion { ROLLER = 0, HIGH_GOAL = 1 };
enum autonType { MAIN = 0, OTHER = 1 };

extern teamColor tc;
extern teamSide ts;
extern autonVersion av;
extern autonType at;

extern void autonInit();
extern void auton(void (* callback)(void), void *arg = nullptr);

// autons
extern void auton_skills();
extern void auton_test();

extern void auton_leftRoller();
extern void auton_leftHighGoal();

extern void auton_rightRoller();
extern void auton_rightHighGoal();