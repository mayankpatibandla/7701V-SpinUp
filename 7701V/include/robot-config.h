#pragma once
#include "vdevices.h"

extern const double deadband;

extern const double forwardCurve;
extern const double turnCurve;

extern brain Brain;
extern controller Controller;
extern controller partnerController;

extern competition Competition;

extern motor lbDriveMtr;
extern motor ltDriveMtr;
extern motor_group leftDriveMtrs;

extern motor rbDriveMtr;
extern motor rtDriveMtr;
extern motor_group rightDriveMtrs;

extern motor_group driveMtrs;

extern togglemotor lFlyMtr;
extern togglemotor rFlyMtr;
extern togglemotor_group flyMtrs;

extern motor lIntakeMtrs;
extern motor rIntakeMtrs;
extern motor_group intakeMtrs;

extern rotation lRot;
extern rotation rRot;
extern rotation sRot;

extern inertial inert;

extern const uint32_t shotCooldown;
extern indexer indexerSlnd;

extern void devicesInit();