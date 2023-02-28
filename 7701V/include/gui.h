#pragma once
#include "auton-manager.h"
#include "odom.h"
#include "robot-config.h"

extern void guiInit();
extern void updateScreen();

extern void drawField();

extern void printOdom();

extern void printOptical();

extern Pose worldToScreen(Pose pose, Pose offset);
extern void drawRobot(Pose offset);