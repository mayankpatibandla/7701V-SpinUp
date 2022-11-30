#pragma once
#include "odom/position-tracking.h"

extern vex::thread positiontracking_thread;
extern void odomInit();

namespace pt = positiontracking;