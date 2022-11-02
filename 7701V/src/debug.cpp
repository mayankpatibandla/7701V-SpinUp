#include "debug.h"
#include "control.h"
#include "driver.h"
#include "robot-config.h"
#include "vex.h"

void debugFlywheel() {
  std::ostringstream strstream;
  strstream.clear();

  strstream << "Left Flywheel Motor Velocity: " << lFlyMtr.velocity(pct);
  Brain.Screen.printAt(0, 20, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
  strstream << "Right Flywheel Motor Velocity: " << rFlyMtr.velocity(pct);
  Brain.Screen.printAt(0, 50, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  strstream << "Left Flywheel Motor Temperature: "
            << lFlyMtr.temperature(celsius);
  Brain.Screen.printAt(0, 90, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
  strstream << "Right Flywheel Motor Temperature: "
            << rFlyMtr.temperature(celsius);
  Brain.Screen.printAt(0, 120, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
}

void debugDrive(const double leftVel, const double rightVel) {
  std::ostringstream strstream;
  strstream.clear();

  strstream << "Left Drive Motor Velocity: " << leftVel << ", "
            << curveJoystick(Controller.Axis3.position(), forwardCurve);
  Brain.Screen.printAt(0, 160, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  strstream << "Right Drive Motor Velocity: " << rightVel << ", "
            << curveJoystick(Controller.Axis1.position(), turnCurve);
  Brain.Screen.printAt(0, 190, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
}

void debugIndexer() {
  Controller.Screen.clearLine(3);
  Controller.Screen.print(Indexer.getAutofiring());
}

void debugOdom() {
  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 20, "Position X  . . . . %8f (in) ",
                       positiontracking::x());
  Brain.Screen.printAt(0, 50, "Position Y  . . . . %8f (in) ",
                       positiontracking::y());
  Brain.Screen.printAt(0, 80, "Theta (-inf, inf) . %8f (rad)",
                       positiontracking::theta());
  Brain.Screen.printAt(0, 110, "Theta [-Pi, Pi) . . %8f (rad)",
                       positiontracking::thetaWrapped(true));
  Brain.Screen.printAt(0, 140, "Theta [0, 2Pi)  . . %8f (rad)",
                       positiontracking::thetaWrapped(false));
  Brain.Screen.printAt(0, 170, "Theta (-inf, inf) . %8f (deg)",
                       positiontracking::theta() * 180 / M_PI);
  Brain.Screen.printAt(0, 200, "Theta [-180, 180) . %8f (deg)",
                       positiontracking::thetaWrapped(true) * 180 / M_PI);
  Brain.Screen.printAt(0, 230, "Theta [0, 360)  . . %8f (deg)",
                       positiontracking::thetaWrapped(false) * 180 / M_PI);
}