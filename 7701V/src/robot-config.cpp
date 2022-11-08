#include "robot-config.h"

brain Brain;

const double deadband = 1;
const double forwardCurve = 3;
const double turnCurve = 5;
controller Controller(primary);
controller partnerController(partner);

competition Competition;

motor lbDriveMtr(PORT2, gearSetting::ratio6_1, false);
motor ltDriveMtr(PORT1, gearSetting::ratio6_1, false);
motor_group leftDriveMtrs(lbDriveMtr, ltDriveMtr);

motor rbDriveMtr(PORT10, gearSetting::ratio6_1, true);
motor rtDriveMtr(PORT9, gearSetting::ratio6_1, true);
motor_group rightDriveMtrs(rbDriveMtr, rtDriveMtr);

motor_group driveMtrs(lbDriveMtr, ltDriveMtr, rbDriveMtr, rtDriveMtr);

const double flywheelCoeffs[] = {0.75, 0.67};
togglemotor lFlyMtr(PORT5, gearSetting::ratio6_1, false);
togglemotor rFlyMtr(PORT7, gearSetting::ratio6_1, true);
togglemotor_group flyMtrs(lFlyMtr, rFlyMtr);

togglemotor lIntakeMtr(PORT11, gearSetting::ratio18_1, false);
togglemotor rIntakeMtr(PORT12, gearSetting::ratio18_1, true);
togglemotor_group intakeMtrs(lIntakeMtr, rIntakeMtr);

motor_group allMtrs(lbDriveMtr, ltDriveMtr, rbDriveMtr, rtDriveMtr, lFlyMtr,
                    rFlyMtr, lIntakeMtr, rIntakeMtr);

// TODO: check reversing
rotation lRot(PORT3, false);
rotation rRot(PORT8, false);
rotation sRot(PORT4, false);

inertial Inertial(PORT20, turnType::left);

const uint32_t shotCooldown = 100;
const uint32_t autofireCooldown = 300;
const uint32_t autofireBtnHoldTime = 300;
indexer Indexer(Brain.ThreeWirePort.B, shotCooldown, autofireCooldown);

void devicesInit() {
  Inertial.calibrate();

  lbDriveMtr.setBrake(brake);
  ltDriveMtr.setBrake(brake);
  rbDriveMtr.setBrake(brake);
  rtDriveMtr.setBrake(brake);

  lFlyMtr.setBrake(coast);
  rFlyMtr.setBrake(coast);

  lIntakeMtr.setBrake(coast);
  rIntakeMtr.setBrake(coast);

  lbDriveMtr.setMaxTorque(100, pct);
  ltDriveMtr.setMaxTorque(100, pct);
  rbDriveMtr.setMaxTorque(100, pct);
  rtDriveMtr.setMaxTorque(100, pct);

  lFlyMtr.setMaxTorque(100, pct);
  rFlyMtr.setMaxTorque(100, pct);

  lIntakeMtr.setMaxTorque(100, pct);
  rIntakeMtr.setMaxTorque(100, pct);

  allMtrs.resetPosition();
  allMtrs.resetRotation();

  lRot.resetPosition();
  rRot.resetPosition();
  sRot.resetPosition();

  waitUntil(!Inertial.isCalibrating());

  Inertial.resetHeading();
  Inertial.resetRotation();
}