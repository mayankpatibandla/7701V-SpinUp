#pragma once
#include "alarm.hpp"
#include "auton-manager.hpp"
#include "odom.hpp"
#include "robot-config.hpp"

extern void guiInit();
extern void updateScreen();

extern void drawField();

extern void printOdom();

extern void printOptical();

extern void printDistance();

extern Pose worldToScreen(Pose pose, Pose offset);
extern void drawRobot(Pose offset);