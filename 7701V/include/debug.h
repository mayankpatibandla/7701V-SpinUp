#pragma once
#include "vex.h"

extern void debugFlywheel();
extern void debugDrive(const double leftVel, const double rightVel);
extern void debugIndexer();
extern void debugOdom();

extern vex::thread debugThread;
extern void debugInit();
extern void debug();