#pragma once
#include "odom.h"
#include "robot-config.h"
#include "vex.h"

struct PID {
  double kP, kI, kD, maxError, dT;

  PID(double kP = 0, double kI = 0, double kD = 0, double maxError = 0,
      double dT = 15)
      : kP(kP), kI(kI), kD(kD), maxError(maxError), dT(dT) {}
};

template <typename T> int sgn(T val) { return (T(0) < val) - (val < T(0)); }

extern void turnToAngle(double theta, int timeout = 0, PID pid = PID());