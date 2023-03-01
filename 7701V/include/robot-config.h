#pragma once
#include "vdevices.h"

extern brain Brain;

extern const double deadband;
extern const double forwardCurve;
extern const double turnCurve;
extern controller Controller;
extern controller partnerController;

extern competition Competition;

extern motor lbDriveMtr;
extern motor lmDriveMtr;
extern motor ltDriveMtr;
extern motor_group leftDriveMtrs;

extern motor rbDriveMtr;
extern motor rmDriveMtr;
extern motor rtDriveMtr;
extern motor_group rightDriveMtrs;

extern motor_group driveMtrs;

extern const double flywheelCoeffs[];
extern togglemotor flyMtr;
extern togglemotor_group flyMtrs;

extern togglemotor intakeMtr;
extern togglemotor_group intakeMtrs;

extern rotation lRot;
extern rotation rRot;
extern rotation sRot;

extern inertial Inertial;

extern int redMin, redMax;
extern int blueMin, blueMax;
extern optical rollerOptical;

extern const uint32_t shotCooldown;
extern const uint32_t autofireCooldown;
extern indexer Indexer;

extern togglepneumatics leftExpansion;
extern togglepneumatics rightExpansion;

extern togglepneumatics angler;

extern void devicesInit();