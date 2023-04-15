#include "debug.h"
#include "control.h"
#include "driver.h"

void debugFlywheel() {
  std::ostringstream strstream;
  strstream.clear();

  strstream << "Flywheel Motor Velocity: " << flyMtr.velocity(pct);
  Brain.Screen.printAt(0, 20, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  strstream << "Flywheel Motor Temperature: " << flyMtr.temperature(celsius);
  Brain.Screen.printAt(0, 90, strstream.str().c_str());
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
  Brain.Screen.printAt(0, 20, "Position X  . . . | %8f (in) ",
                       positiontracking::x());
  Brain.Screen.printAt(0, 50, "Position Y  . . . | %8f (in) ",
                       positiontracking::y());
  Brain.Screen.printAt(0, 80, "Theta (-inf, inf) | %8f (rad)",
                       positiontracking::theta());
  Brain.Screen.printAt(0, 110, "Theta [-Pi, Pi) . | %8f (rad)",
                       positiontracking::thetaWrapped(true));
  Brain.Screen.printAt(0, 140, "Theta [0, 2Pi)  . | %8f (rad)",
                       positiontracking::thetaWrapped(false));
  Brain.Screen.printAt(0, 170, "Theta (-inf, inf) | %8f (deg)",
                       positiontracking::theta() * 180 / M_PI);
  Brain.Screen.printAt(0, 200, "Theta [-180, 180) | %8f (deg)",
                       positiontracking::thetaWrapped(true) * 180 / M_PI);
  Brain.Screen.printAt(0, 230, "Theta [0, 360)  . | %8f (deg)",
                       positiontracking::thetaWrapped(false) * 180 / M_PI);
}

void debugOptical() {
  std::ostringstream strstream;
  strstream.clear();
  // TODO: use both optical sensors
  Brain.Screen.printAt(240, 120, "Optical Hue: %8f", leftRollerOptical.hue());
  strstream << "Optical Color: "
            << (leftRollerOptical.color() == blue
                    ? "BLUE"
                    : leftRollerOptical.color() == red ? "RED" : "OTHER");
  Brain.Screen.printAt(240, 140, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
}

vex::thread debugThread;

void debugInit() { debugThread = vex::thread(debug); }

void debug() {
  // while (true) {
  //   debugOptical();
  //   this_thread::sleep_for(50);
  // }
}