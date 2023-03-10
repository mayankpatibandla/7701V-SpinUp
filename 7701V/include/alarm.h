#pragma once
#include "robot-config.h"

extern void error(vex::device *Device);
extern void checkDevices();

extern std::string deviceTypeToString(V5_DeviceType deviceType);