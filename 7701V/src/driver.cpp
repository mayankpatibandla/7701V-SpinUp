#include "driver.h"
#include "auton-manager.h"
#include "control.h"

double curveJoystick(double input, const double t) {
  input /= 100;
  return input * std::exp(t * (std::abs(input) - 1));
}

bool expandAllReady = true;
bool expandTopReady = true;
bool expandBottomLeftReady = true;
bool expandBottomRightReady = true;

bool indexerReady = true;

void driverInit() {
  Controller.ButtonX.pressed([]() { flyMtrs.toggleState(); });
  Controller.ButtonY.pressed([]() { angler.toggle(); });

  Controller.ButtonA.pressed([]() { Indexer.startAutofiring(); });
  Controller.ButtonA.released([]() { Indexer.stopAutofiring(); });
}

void driver() {
  if (Competition.isCompetitionSwitch() || Competition.isFieldControl()) {
    flyMtrs.setState(true);
    angler.set(false);
    matchLoadEnabled = false;
  }

  while (true) {
    // Auton test
    if ((!Competition.isCompetitionSwitch() && !Competition.isFieldControl()) &&
        (Controller.ButtonRight.pressing() && Controller.ButtonUp.pressing())) {
      auton();
    }

    // Flywheel
    double flywheelSpeed = Controller.ButtonR1.pressing()
                               ? flywheelCoeffs[0]
                               : Controller.ButtonR2.pressing()
                                     ? flywheelCoeffs[1]
                                     : Controller.ButtonB.pressing()
                                           ? flywheelMatchLoadCoeff
                                           : flywheelCoeffs[2];

    if (Controller.ButtonLeft.pressing() && Controller.ButtonDown.pressing()) {
      flyMtrs.spin(fwd, flywheelSpeed * -12, volt);
    } else {
      flyMtrs.spin(fwd, flyMtrs.getState() * flywheelSpeed * 12, volt);
    }

    // Indexer toggle
    if (Controller.ButtonDown.pressing() && indexerReady &&
        !Controller.ButtonLeft.pressing() && !Controller.ButtonR1.pressing() &&
        !Controller.ButtonR2.pressing() && !Controller.ButtonRight.pressing() &&
        !Controller.ButtonUp.pressing() && !Controller.ButtonL1.pressing() &&
        !Controller.ButtonL2.pressing()) {
      Indexer.toggle();
      indexerReady = false;
    }
    if (!Controller.ButtonDown.pressing()) {
      indexerReady = true;
    }

    // Match loads
    matchLoadEnabled = Controller.ButtonB.pressing();

    // Intake
    if (Controller.ButtonL1.pressing() && !Controller.ButtonL2.pressing() &&
        !Controller.ButtonLeft.pressing()) {
      intakeMtrs.spin(fwd, -12, volt);
      intakeMtrs.setState(false);
    } else if (Controller.ButtonL2.pressing() &&
               !Controller.ButtonL1.pressing() &&
               !Controller.ButtonLeft.pressing()) {
      intakeMtrs.spin(fwd, 12, volt);
      intakeMtrs.setState(false);
    } else if (intakeMtrs.getState()) {
      intakeMtrs.spin(fwd, 12, volt);
    } else {
      intakeMtrs.stop();
    }

    // Drive
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

    // Expansion
    if (Controller.ButtonL1.pressing() && Controller.ButtonL2.pressing() &&
        Controller.ButtonR1.pressing() && Controller.ButtonR2.pressing() &&
        !Controller.ButtonLeft.pressing()) {
      if (expandAllReady) {
        expandAllReady = false;
        flyMtrs.setState(false);
        expandAll();
      }
    } else if (!Controller.ButtonL1.pressing() &&
               !Controller.ButtonL2.pressing() &&
               !Controller.ButtonR1.pressing() &&
               !Controller.ButtonR2.pressing()) {
      expandAllReady = true;
    }
    if (Controller.ButtonLeft.pressing()) {
      if (Controller.ButtonR2.pressing() && expandBottomRightReady) {
        expandBottomRightReady = false;
        flyMtrs.setState(false);
        expandRight();
      } else if (!Controller.ButtonR2.pressing()) {
        expandBottomRightReady = true;
      }

      if (Controller.ButtonL2.pressing() && expandBottomLeftReady) {
        expandBottomLeftReady = false;
        flyMtrs.setState(false);
        expandLeft();
      } else if (!Controller.ButtonL2.pressing()) {
        expandBottomLeftReady = true;
      }

      if (Controller.ButtonL1.pressing() && Controller.ButtonR1.pressing() &&
          expandTopReady) {
        expandTopReady = false;
        flyMtrs.setState(false);
        expandTop();
      } else if (!Controller.ButtonL1.pressing() &&
                 !Controller.ButtonR1.pressing()) {
        expandTopReady = true;
      }
    }

    this_thread::sleep_for(1);
  }
}