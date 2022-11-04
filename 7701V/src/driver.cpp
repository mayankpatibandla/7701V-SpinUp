#include "driver.h"
#include "auton-manager.h"
#include "debug.h"

double curveJoystick(double input, const double t) {
  input /= 100;
  return input * std::exp(t * (std::abs(input) - 1));
}

void driverInit() {
  Controller.ButtonX.pressed([]() { flyMtrs.toggleState(); });
  Controller.ButtonA.pressed([]() { Indexer.shootDisc(); });
}

void driver() {
  while (true) {
    bool flywheelSlow = Controller.ButtonR1.pressing();

    flyMtrs.spin(
        fwd, (flyMtrs.getState() / (flywheelSlow / flywheelSlowCoeff + 1)) * 12,
        volt);

    if (Controller.ButtonUp.pressing() && Controller.ButtonLeft.pressing()) {
      Indexer.set(false);
    }
    Indexer.setAutofiring(Controller.ButtonY.pressing());

    if (Controller.ButtonL1.pressing()) {
      intakeMtrs.spin(fwd, 12, volt);
    } else if (Controller.ButtonL2.pressing()) {
      intakeMtrs.spin(fwd, -12, volt);
    } else {
      intakeMtrs.stop();
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
    // debugFlywheel();
    debugOdom();
    Brain.Screen.render();

    this_thread::sleep_for(1);
  }
}