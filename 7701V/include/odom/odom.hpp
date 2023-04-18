#pragma once
#include "odom/position-tracking.hpp"

extern vex::thread positiontracking_thread;
extern void odomInit();

namespace pt = positiontracking;