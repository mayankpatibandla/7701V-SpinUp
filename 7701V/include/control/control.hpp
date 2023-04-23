#pragma once
#include "config/auton-manager.hpp"
#include "config/robot-config.hpp"
#include "odom/odom.hpp"
#include "vex/vex.hpp"

struct PID {
  double kP, kI, kD, maxError, dT;

  PID(double kP = 0, double kI = 0, double kD = 0, double maxError = 0,
      double dT = 15)
      : kP(kP), kI(kI), kD(kD), maxError(maxError), dT(dT) {}
};

extern bool matchLoadEnabled;

extern void expandAll();
extern void expandBottom();
extern void expandTop();
extern void expandLeft();
extern void expandRight();

extern void spinRoller(double velocity = -1, color col = rollerColor,
                       int minTime = 0, int maxTime = 0);

extern void turnToAngle(double theta, int minTime = 0, int maxTime = 0,
                        double maxVelocity = 1, PID pid = {0.5, 0, 0, 0.17});
extern void driveRelative(double distance, int minTime = 0, int maxTime = 0,
                          double maxVelocity = 1, PID pid = {0.001, 0, 0, 6});