#include "robot-config.h"

const double deadband = 1;

const double forwardCurve = 3;
const double turnCurve = 3;

brain Brain;
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

togglemotor lFlyMtr(PORT5, gearSetting::ratio6_1, false);
togglemotor rFlyMtr(PORT7, gearSetting::ratio6_1, true);
togglemotor_group flyMtrs(lFlyMtr, rFlyMtr);

// TODO: update ports
motor lIntakeMtr(11, gearSetting::ratio6_1, false);
motor rIntakeMtr(12, gearSetting::ratio6_1, true);
motor_group intakeMtrs(lIntakeMtr, rIntakeMtr);

// TODO: check reversing
rotation lRot(PORT3, false);
rotation rRot(PORT8, false);
rotation sRot(PORT4, false);

togglepneumatics indexerSlnd(Brain.ThreeWirePort.A);