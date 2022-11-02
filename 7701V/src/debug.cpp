#include "debug.h"
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

void debugIndexer(){
  Controller.Screen.clearLine(3);
  Controller.Screen.print(Indexer.getAutofiring());
}