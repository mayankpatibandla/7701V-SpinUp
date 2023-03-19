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

const double flywheelCoeffs[] = {1, 0.7, 0.79};
const double flywheelMatchLoadCoeff = 0.71, flywheelMinCoeff = 0.45;
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

int redMin = 340, redMax = 20;
int blueMin = 225, blueMax = 265;
optical rollerOptical(PORT3, false);

int matchLoadStartDelay = 450, matchLoadEndDelay = 500;
int storageDistMin = 3, storageDistMax = 175;
distance storageDistance(PORT4);

const uint32_t shotCooldown = 125;
const uint32_t autofireCooldown = 200;
indexer Indexer(Brain.ThreeWirePort.B, shotCooldown, autofireCooldown);

togglepneumatics leftExpansion(Brain.ThreeWirePort.C);
togglepneumatics rightExpansion(Brain.ThreeWirePort.A);

togglepneumatics angler(Brain.ThreeWirePort.D);

std::vector<alarmDevice> devicesList;

void devicesListInit() {
  devicesList.reserve(21);

  devicesList.push_back({&lbDriveMtr, "Left Bottom Drive", "Motor"});
  devicesList.push_back({&lmDriveMtr, "Left Middle Drive", "Motor"});
  devicesList.push_back({&ltDriveMtr, "Left Top Drive", "Motor"});

  devicesList.push_back({&rbDriveMtr, "Right Bottom Drive", "Motor"});
  devicesList.push_back({&rmDriveMtr, "Right Middle Drive", "Motor"});
  devicesList.push_back({&rtDriveMtr, "Right Top Drive", "Motor"});

  devicesList.push_back({&flyMtr, "Flywheel", "Motor"});

  devicesList.push_back({&intakeMtr, "Intake", "Motor"});

  devicesList.push_back({&lRot, "Left Tracking Wheel", "Rotation"});
  devicesList.push_back({&rRot, "Right Tracking Wheel", "Rotation"});
  devicesList.push_back({&sRot, "Back Tracking Wheel", "Rotation"});

  devicesList.push_back({&Inertial, "Inertial", "Inertial"});

  devicesList.push_back({&rollerOptical, "Roller Color", "Optical"});

  devicesList.push_back({&storageDistance, "Disc Storage", "Distance"});
}

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