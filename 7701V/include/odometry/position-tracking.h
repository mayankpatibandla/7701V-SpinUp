#pragma once
#include "robot-config.h"
#include "vex.h"

namespace positiontracking {
extern void positiontracking();

extern double x();
extern double y();
extern double theta();

extern double thetaWrapped(bool range = true);

extern double plrR();
extern double plrTheta();

extern const double WHEEL_RADIUS;
} // namespace positiontracking