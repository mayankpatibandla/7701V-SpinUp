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
extern const double flywheelMatchLoadCoeff, flywheelMinCoeff;
extern togglemotor flyMtr;
extern togglemotor_group flyMtrs;

extern togglemotor intakeMtr;
extern togglemotor_group intakeMtrs;

extern rotation lRot;
extern rotation rRot;
extern rotation sRot;

extern inertial Inertial;

extern double redMin, redMax;
extern double blueMin, blueMax;
extern optical leftRollerOptical;
extern optical rightRollerOptical;

extern int matchLoadStartDelay, matchLoadEndDelay;
extern double storageDistMin, storageDistMax;
extern distance storageDistance;

extern const uint32_t shotCooldown;
extern const uint32_t autofireCooldown;
extern indexer Indexer;

extern togglepneumatics angler;

extern togglepneumatics topRightExpansion;
extern togglepneumatics topLeftExpansion;
extern togglepneumatics bottomRightExpansion;
extern togglepneumatics bottomLeftExpansion;

typedef struct {
  vex::device *device;
  std::string name, type;
} alarmDevice;

extern std::vector<alarmDevice> devicesList;
extern void devicesListInit();

extern void devicesInit();