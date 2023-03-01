#include "robot-config.h"

brain Brain;

const double deadband = 1;
const double forwardCurve = 1;
const double turnCurve = 0.1;
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

motor_group driveMtrs(lbDriveMtr, lmDriveMtr, ltDriveMtr, rbDriveMtr,
                      rmDriveMtr, rtDriveMtr);

const double flywheelCoeffs[] = {1, 0.88, 0.7};
togglemotor flyMtr(PORT1, gearSetting::ratio6_1, true);
togglemotor_group flyMtrs(flyMtr);

togglemotor intakeMtr(PORT2, gearSetting::ratio18_1, true);
togglemotor_group intakeMtrs(intakeMtr);

motor_group allMtrs(lbDriveMtr, lmDriveMtr, ltDriveMtr, rbDriveMtr, rmDriveMtr,
                    rtDriveMtr, flyMtr, intakeMtr);

rotation lRot(PORT15, true);
rotation rRot(PORT16, false);
rotation sRot(PORT17, false);

inertial Inertial(PORT14, turnType::right);

int redMin = 350, redMax = 50;
int blueMin = 200, blueMax = 300;
optical rollerOptical(PORT3, false);

const uint32_t shotCooldown = 125;
const uint32_t autofireCooldown = 200;
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

  flyMtr.setBrake(coast);

  intakeMtr.setBrake(brake);

  lbDriveMtr.setMaxTorque(100, pct);
  ltDriveMtr.setMaxTorque(100, pct);
  rbDriveMtr.setMaxTorque(100, pct);
  rtDriveMtr.setMaxTorque(100, pct);

  flyMtr.setMaxTorque(100, pct);

  intakeMtr.setMaxTorque(100, pct);

  allMtrs.resetPosition();
  allMtrs.resetRotation();

  lRot.resetPosition();
  rRot.resetPosition();
  sRot.resetPosition();

  rollerOptical.setLight(ledState::on);
  rollerOptical.setLightPower(100, pct);

  waitUntil(!Inertial.isCalibrating());

  Inertial.resetHeading();
  Inertial.resetRotation();
}