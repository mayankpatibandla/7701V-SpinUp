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

template <typename T> int sgn(const T &val) {
  return (T(0) < val) - (val < T(0));
}
template <typename T> T clamp(const T &n, const T &lower, const T &upper) {
  return std::max(lower, std::min(n, upper));
}

extern void turnToAngle(double theta, int minTime = 0, int maxTime = 0,
                        PID pid = {});
extern void driveRelative(double distance, int minTime = 0, int maxTime = 0,
                          PID pid = {});