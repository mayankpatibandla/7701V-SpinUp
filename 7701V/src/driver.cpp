#include "driver.h"
#include "auton-manager.h"

double curveJoystick(double input, const double t) {
  input /= 100;
  return input * std::exp(t * (std::abs(input) - 1));
}

uint32_t autofireStartTime = 0;
uint32_t autofireDeltaTime = 0;

void driverInit() {
  Controller.ButtonX.pressed([]() { flyMtrs.toggleState(); });
  Controller.ButtonB.pressed([]() { intakeMtrs.toggleState(); });

  Controller.ButtonA.pressed([]() {
    Indexer.shootDisc();
    autofireStartTime = Brain.Timer.system();
  });
  Controller.ButtonA.released([]() {
    Indexer.stopAutofiring();
    autofireStartTime = 0;
  });
}

void driver() {
  while (true) {
    // Flywheel
    double flywheelSlow = Controller.ButtonR1.pressing()
                              ? 1
                              : Controller.ButtonR2.pressing()
                                    ? flywheelCoeffs[1]
                                    : flywheelCoeffs[0];
    double flywheelReverse =
        Controller.ButtonLeft.pressing() && Controller.ButtonDown.pressing()
            ? -1
            : 1;

    flyMtrs.spin(fwd, flyMtrs.getState() * flywheelSlow * flywheelReverse * 12,
                 volt);

    // Indexer
    autofireDeltaTime = Brain.Timer.system() - autofireStartTime;
    if (Controller.ButtonA.pressing()) {
      if (autofireDeltaTime > Indexer.getAutofireCooldown()) {
        Indexer.startAutofiring();
      }
    }

    // Indexer emergency retract
    if (Controller.ButtonUp.pressing() && Controller.ButtonLeft.pressing()) {
      Indexer.set(false);
    }

    // Intake
    if (Controller.ButtonL1.pressing()) {
      intakeMtrs.spin(fwd, -12, volt);
      intakeMtrs.setState(false);
    } else if (Controller.ButtonL2.pressing()) {
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

    // Auton test
    if ((!Competition.isCompetitionSwitch() && !Competition.isFieldControl()) &&
        (Controller.ButtonRight.pressing() && Controller.ButtonUp.pressing())) {
      auton();
    }

    this_thread::sleep_for(1);
  }
}