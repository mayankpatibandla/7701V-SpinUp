#pragma once
#include "odom.h"
#include "robot-config.h"

extern void guiInit();
extern void updateScreen();

extern void drawField();

extern void printOdom();

extern Pose worldToScreen(Pose pose, Pose offset);
extern void drawRobot(Pose offset);