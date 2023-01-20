#include "robot-config.h"

brain Brain;

const double deadband = 1;
const double forwardCurve = 1;
const double turnCurve = 1;
controller Controller(primary);
controller partnerController(partner);

competition Competition;

motor lbDriveMtr(PORT11, gearSetting::ratio6_1, true);
motor lmDriveMtr(PORT12, gearSetting::ratio6_1, false);
motor ltDriveMtr(PORT13, gearSetting::ratio6_1, true);
motor_group leftDriveMtrs(lbDriveMtr, lmDriveMtr, ltDriveMtr);

motor rbDriveMtr(PORT20, gearSetting::ratio6_1, false);
motor rmDriveMtr(PORT19, gearSetting::ratio6_1, true);
motor rtDriveMtr(PORT18, gearSetting::ratio6_1, false);
motor_group rightDriveMtrs(rbDriveMtr, rmDriveMtr, rtDriveMtr);

motor_group driveMtrs(lbDriveMtr, lmDriveMtr, ltDriveMtr, rbDriveMtr, rmDriveMtr, rtDriveMtr);

const double flywheelCoeffs[] = {0.875, 0.6667};
togglemotor lFlyMtr(PORT1, gearSetting::ratio6_1, true);
togglemotor rFlyMtr(PORT22, gearSetting::ratio6_1, false);
togglemotor_group flyMtrs(lFlyMtr, rFlyMtr);

togglemotor lIntakeMtr(PORT2, gearSetting::ratio18_1, true);
togglemotor rIntakeMtr(PORT22, gearSetting::ratio18_1, false);
togglemotor_group intakeMtrs(lIntakeMtr, rIntakeMtr);

motor_group allMtrs(lbDriveMtr, lmDriveMtr, ltDriveMtr, rbDriveMtr, rmDriveMtr, rtDriveMtr, lFlyMtr,
                    rFlyMtr, lIntakeMtr, rIntakeMtr);

rotation lRot(PORT22, false);
rotation rRot(PORT22, true);
rotation sRot(PORT22, true);

inertial Inertial(PORT22, turnType::right);

const uint32_t shotCooldown = 150;
const uint32_t autofireCooldown = 500;
indexer Indexer(Brain.ThreeWirePort.B, shotCooldown, autofireCooldown);

togglepneumatics leftExpansion(Brain.ThreeWirePort.C);
togglepneumatics rightExpansion(Brain.ThreeWirePort.A);

togglepneumatics angler(Brain.ThreeWirePort.D);

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