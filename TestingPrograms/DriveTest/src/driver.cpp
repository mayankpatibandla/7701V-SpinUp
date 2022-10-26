#include "driver.h"
#include "debug.h"


double curveJoystick(double input, const double t) {
  input /= 100;
  return input * std::exp(t * (std::abs(input) - 1));
}

void driver() {
  // ButtonA: indexer manual
  // ButtonLeft: auto fire indexer
  // ButtonRight && ButtonDown: auton test
  // ButtonR1: hold for slow flywheel
  // ButtonL1, L2: intake
  while (true) {
    bool flywheelSlow = !Controller.ButtonR1.pressing();

    flyMtrs.spin(fwd, (flyMtrs.getState() / (flywheelSlow / 1.67 + 1)) * 12,
                 volt);

    double leftVel = curveJoystick(Controller.Axis3.position(), forwardCurve) +
                     curveJoystick(Controller.Axis1.position(), turnCurve);
    double rightVel = curveJoystick(Controller.Axis3.position(), forwardCurve) -
                      curveJoystick(Controller.Axis1.position(), turnCurve);
    if (abs(Controller.Axis1.position()) > deadband ||
        abs(Controller.Axis3.position()) > deadband) {
      leftDriveMtrs.spin(fwd, leftVel * 12, volt);
      rightDriveMtrs.spin(fwd, rightVel * 12, volt);
    } else {
      driveMtrs.stop();
    }

    Brain.Screen.clearScreen();
    debugFlywheel();
    debugDrive(leftVel, rightVel);
    Brain.Screen.render();
  }
}