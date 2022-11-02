#include "driver.h"
#include "auton-manager.h"
#include "debug.h"

double curveJoystick(double input, const double t) {
  input /= 100;
  return input * std::exp(t * (std::abs(input) - 1));
}

void driverInit() {
  Controller.ButtonX.pressed([]() { flyMtrs.toggleState(); });
  Controller.ButtonA.pressed([]() { indexerSlnd.shootDisc(); });
}

void driver() {
  // ButtonLeft: auto fire indexer
  // ButtonL1, L2: intake
  while (true) {
    bool flywheelSlow = Controller.ButtonR1.pressing();

    flyMtrs.spin(fwd, (flyMtrs.getState() / (flywheelSlow / 1.5 + 1)) * 12,
                 volt);

    if (Controller.ButtonUp.pressing() && Controller.ButtonLeft.pressing()) {
      indexerSlnd.set(false);
    } else if (Controller.ButtonLeft.pressing()) {
      shootDisc();
    }

    double leftVel = curveJoystick(Controller.Axis3.position(), forwardCurve) +
                     curveJoystick(Controller.Axis1.position(), turnCurve);
    double rightVel = curveJoystick(Controller.Axis3.position(), forwardCurve) -
                      curveJoystick(Controller.Axis1.position(), turnCurve);
    if (abs(Controller.Axis1.position()) > deadband ||
        abs(Controller.Axis3.position()) > deadband) {
      leftDriveMtrs.spin(fwd, leftVel * 12, volt);
      rightDriveMtrs.spin(fwd, rightVel * 12, volt);
    } else {
      driveMtrs.stop(brake);
    }

    if ((!Competition.isCompetitionSwitch() && !Competition.isFieldControl()) &&
        (Controller.ButtonRight.pressing() &&
         Controller.ButtonDown.pressing())) {
      auton();
    }

    Brain.Screen.clearScreen();
    debugFlywheel();
    debugDrive(leftVel, rightVel);
    Brain.Screen.render();
  }
}