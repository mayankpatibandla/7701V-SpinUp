#include "driver.h"
#include "auton-manager.h"
#include "debug.h"

double curveJoystick(double input, const double t) {
  input /= 100;
  return input * std::exp(t * (std::abs(input) - 1));
}

void driverInit() {
  Controller.ButtonB.pressed([]() { flyMtrs.toggleState(); });
  Controller.ButtonX.pressed([]() { intakeMtrs.toggleState(); });
}

void driver() {
  /*
      A (hold): autofire
[done]B: flywheel
[done]X: Intake in (toggle)
[not needed]Y: Intake out (hold), disable toggle
[done?]Left and down: flywheel reverse
  */
  while (true) {
    double flywheelSlow =
        Controller.ButtonR1.pressing()
            ? flywheelCoeff1
            : Controller.ButtonR2.pressing() ? flywheelCoeff2 : 1;
    double flywheelReverse =
        Controller.ButtonLeft.pressing() && Controller.ButtonDown.pressing()
            ? -1
            : 1;

    flyMtrs.spin(
        fwd, flyMtrs.getState() * flywheelSlow * flywheelReverse * 12, volt);

    if (Controller.ButtonUp.pressing() && Controller.ButtonLeft.pressing()) {
      Indexer.set(false);
    }
    Indexer.setAutofiring(Controller.ButtonY.pressing());

    if (Controller.ButtonL1.pressing()) {
      intakeMtrs.spin(fwd, 12, volt);
      intakeMtrs.setState(false);
    } else if (Controller.ButtonL2.pressing()) {
      intakeMtrs.spin(fwd, -12, volt);
      intakeMtrs.setState(false);
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
        (Controller.ButtonRight.pressing() && Controller.ButtonUp.pressing())) {
      auton();
    }

    Brain.Screen.clearScreen();
    // debugFlywheel();
    debugOdom();
    Brain.Screen.render();

    this_thread::sleep_for(1);
  }
}