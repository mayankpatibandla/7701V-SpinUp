#pragma once
#include "config/robot-config.hpp"
#include "vex/vex.hpp"

struct Pose {
  double x, y, theta;
};

namespace positiontracking {
extern void positiontracking();

extern double x();
extern double y();
extern double theta();
extern Pose pose();

extern double thetaWrapped(bool range = true);

extern double plrR();
extern double plrTheta();

extern const double WHEEL_RADIUS;
} // namespace positiontracking