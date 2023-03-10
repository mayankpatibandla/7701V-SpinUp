#include "alarm.h"

void error(vex::device *Device) {
  std::ostringstream strstream;
  strstream.clear();

  strstream << "PORT: " << Device->index() + 1
            << " TYPE: " << deviceTypeToString(Device->type());

  Brain.Screen.setFont(mono30);
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(white);

  Brain.Screen.clearScreen();
  Brain.Screen.printAt(0, 40, "DEVICE NOT FOUND");
  Brain.Screen.printAt(0, 70, strstream.str().c_str());
  Brain.Screen.render();

  while (true) {
    Controller.rumble(rumbleLong);

    // break loop on any input
    if (Controller.ButtonA.pressing() || Controller.ButtonB.pressing() ||
        Controller.ButtonX.pressing() || Controller.ButtonY.pressing() ||
        Controller.ButtonUp.pressing() || Controller.ButtonDown.pressing() ||
        Controller.ButtonLeft.pressing() || Controller.ButtonRight.pressing() ||
        Controller.ButtonL1.pressing() || Controller.ButtonL2.pressing() ||
        Controller.ButtonR1.pressing() || Controller.ButtonR2.pressing() ||
        Controller.Axis3.position() < -50 ||
        Controller.Axis4.position() < -50 || Controller.Axis3.position() > 50 ||
        Controller.Axis4.position() > 50 || Controller.Axis1.position() < -50 ||
        Controller.Axis2.position() < -50 || Controller.Axis1.position() > 50 ||
        Controller.Axis2.position() > 50 || Brain.Screen.pressing()) {
      break;
    } else {
      this_thread::sleep_for(100);
    }
  }
}

void checkDevices() {
  for (auto &i : devicesList) {
    if (!i->installed()) {
      error(i);
    }
  }
}

std::string deviceTypeToString(V5_DeviceType deviceType) {
  switch (deviceType) {
  case kDeviceTypeNoSensor: {
    return "None";
  } break;
  case kDeviceTypeMotorSensor: {
    return "Motor";
  } break;
  case kDeviceTypeLedSensor: {
    return "Led";
  } break;
  case kDeviceTypeAbsEncSensor: {
    return "AbsEnc";
  } break;
  case kDeviceTypeCrMotorSensor: {
    return "CrMotor";
  } break;
  case kDeviceTypeImuSensor: {
    return "Imu";
  } break;
  // obsolete
  // case kDeviceTypeRangeSensor: {
  //   return "Range";
  // } break;
  case kDeviceTypeDistanceSensor: {
    return "Distance";
  } break;
  case kDeviceTypeRadioSensor: {
    return "Radio";
  } break;
  case kDeviceTypeTetherSensor: {
    return "Tether";
  } break;
  case kDeviceTypeBrainSensor: {
    return "Brain";
  } break;
  case kDeviceTypeVisionSensor: {
    return "Vision";
  } break;
  case kDeviceTypeAdiSensor: {
    return "Adi";
  } break;
  case kDeviceTypeRes1Sensor: {
    return "Res1";
  } break;
  case kDeviceTypeRes2Sensor: {
    return "Res2";
  } break;
  case kDeviceTypeRes3Sensor: {
    return "Res3";
  } break;
  case kDeviceTypeOpticalSensor: {
    return "Optical";
  } break;
  case kDeviceTypeMagnetSensor: {
    return "Magnet";
  } break;
  case kDeviceTypeGpsSensor: {
    return "GPS";
  } break;
  case kDeviceTypeBumperSensor: {
    return "Bumper";
  } break;
  case kDeviceTypeGyroSensor: {
    return "Gyro";
  } break;
  case kDeviceTypeSonarSensor: {
    return "Sonar";
  } break;
  case kDeviceTypeGenericSensor: {
    return "Generic";
  } break;
  case kDeviceTypeGenericSerial: {
    return "Serial";
  } break;
  case kDeviceTypeUndefinedSensor: {
    return "Undefined";
  } break;
  default: {
    return "Unknown";
  } break;
  }
}