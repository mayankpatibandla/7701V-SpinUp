/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\mayan                                            */
/*    Created:      Thu Aug 18 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;
vex::motor RightFrntmotor = vex::motor( vex::PORT1,true);
vex::motor RightBckmotor = vex::motor( vex::PORT2,true);
vex::motor LeftFrntmotor= vex::motor( vex::PORT3,true);
vex::motor LeftBckmotor= vex::motor( vex::PORT4,true);
vex::motor CallOfDuty= vex::motor( vex::PORT5,true);
vex::motor CallOfDuty2= vex::motor( vex::PORT6,true);
vex::controller Controller1= vex::controller();
vex::digital_out dig1 = digital_out( Brain.ThreeWirePort.H );
// define your global instances of motors and other devices here

//---------------------------------------------------------------------------/
/* Pre-Autonomous Functions /
/ /
/ You may want to perform some actions before the competition starts. /
/ Do them in the following function. You must return from this function /
/ or the autonomous and usercontrol tasks will not be started. This /
/ function is only called once after the V5 has been powered on and /
/ not every time that the robot is disabled. /
/---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, …
};

//---------------------------------------------------------------------------/
/* /
/ Autonomous Task /
/ /
/ This task is used to control your robot during the autonomous phase of /
/ a VEX Competition. /
/ /
/ You must modify the code to add your own robot specific commands here. /
/---------------------------------------------------------------------------*/

void autonomous(void) {
  //Forward
  RightFrntmotor.startRotateFor(vex::directionType::fwd, 1000, vex::rotationUnits::deg);
  RightBckmotor.startRotateFor(vex::directionType::fwd, 1000, vex::rotationUnits::deg);
  LeftFrntmotor.startRotateFor(vex::directionType::fwd, 1000, vex::rotationUnits::deg);
  LeftBckmotor.rotateFor(vex::directionType::fwd, 1000, vex::rotationUnits::deg);//starter

  //Right(swing)
  LeftFrntmotor.startRotateFor(vex::directionType::fwd, 900, vex::rotationUnits::deg);
  LeftBckmotor.rotateFor(vex::directionType::fwd, 900, vex::rotationUnits::deg);//starter

  //Left(swing)
  RightFrntmotor.startRotateFor(vex::directionType::fwd, 900, vex::rotationUnits::deg);
  RightBckmotor.rotateFor(vex::directionType::fwd, 900, vex::rotationUnits::deg);//starter

  //right(close)
  LeftFrntmotor.startRotateFor(vex::directionType::fwd, 900, vex::rotationUnits::deg);
  LeftBckmotor.startRotateFor(vex::directionType::fwd, 900, vex::rotationUnits::deg);
  RightFrntmotor.startRotateFor(vex::directionType::rev, 900, vex::rotationUnits::deg);
  RightBckmotor.rotateFor(vex::directionType::rev, 900, vex::rotationUnits::deg);//starter

  //left(close)
  RightFrntmotor.startRotateFor(vex::directionType::rev, 900, vex::rotationUnits::deg);
  RightBckmotor.startRotateFor(vex::directionType::rev, 900, vex::rotationUnits::deg);
  LeftFrntmotor.startRotateFor(vex::directionType::fwd, 900, vex::rotationUnits::deg);
  LeftBckmotor.rotateFor(vex::directionType::fwd, 900, vex::rotationUnits::deg); //starter
}

//---------------------------------------------------------------------------/
/* /
/ User Control Task /
/ /
/ This task is used to control your robot during the user control phase of /
/ a VEX Competition. /
/ /
/ You must modify the code to add your own robot specific commands here. /
/---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    RightFrntmotor.spin(vex::directionType::rev, (Controller1.Axis1.value() + Controller1.Axis2.value()), vex::velocityUnits::pct);
    RightBckmotor.spin(vex::directionType::rev, (Controller1.Axis1.value() + Controller1.Axis2.value()), vex::velocityUnits::pct);
    LeftFrntmotor.spin(vex::directionType::fwd, (Controller1.Axis1.value() - Controller1.Axis2.value()), vex::velocityUnits::pct);
    LeftBckmotor.spin(vex::directionType::fwd, (Controller1.Axis1.value() - Controller1.Axis2.value()), vex::velocityUnits::pct);
    CallOfDuty.spin(vex::directionType::fwd, -Controller1.ButtonR2.pressing()*100, vex::velocityUnits::pct);
    CallOfDuty2.spin(vex::directionType::fwd, -Controller1.ButtonR2.pressing()*100, vex::velocityUnits::pct);
  }
  // …
  // Insert user code here. This is where you use the joystick values to
  // update your motors, etc.
  // …
  RightFrntmotor.spin(vex::directionType::rev, (Controller1.Axis2.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
  RightBckmotor.spin(vex::directionType::rev, (Controller1.Axis2.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
  LeftFrntmotor.spin(vex::directionType::fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);
  LeftBckmotor.spin(vex::directionType::fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);

  wait(8, msec); // Sleep the task for a short amount of time to prevent wasted resources.
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  while(1) {
    int count = 1;
    if( Controller1.ButtonL1.pressing() ) {
      dig1.set( true );
    }
    else{
      dig1.set( false );
    }
    this_thread::sleep_for(10);
  }

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
