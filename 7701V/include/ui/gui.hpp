#pragma once
#include "ui/alarm.hpp"
#include "config/auton-manager.hpp"
#include "odom/odom.hpp"
#include "config/robot-config.hpp"

extern void guiInit();
extern void updateScreen();

extern void drawField();

extern void printOdom();

extern void printOptical();

extern void printDistance();

extern Pose worldToScreen(Pose pose, Pose offset);
extern void drawRobot(Pose offset);