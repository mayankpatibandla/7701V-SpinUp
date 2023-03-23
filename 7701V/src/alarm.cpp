#include "alarm.h"

bool dismissed = false;

void error(alarmDevice *Device) {
  std::ostringstream strstream;
  strstream.clear();

  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(white);

  Brain.Screen.clearScreen();

  Brain.Screen.setFont(mono60);
  Brain.Screen.printAt(0, 40, "DEVICE NOT FOUND");

  Brain.Screen.setFont(mono40);

  strstream << "Port: " << Device->device->index() + 1;
  Brain.Screen.printAt(0, 110, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  strstream << "Type: " << Device->type;
  Brain.Screen.printAt(0, 155, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  strstream << "Name: " << Device->name;
  Brain.Screen.printAt(0, 200, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  Brain.Screen.render();

  while (!Device->device->installed() && !dismissed) {
    Controller.rumble(rumbleLong);

    // break on any button press
    if (Controller.ButtonA.pressing() || Controller.ButtonB.pressing() ||
        Controller.ButtonX.pressing() || Controller.ButtonY.pressing() ||
        Controller.ButtonUp.pressing() || Controller.ButtonDown.pressing() ||
        Controller.ButtonLeft.pressing() || Controller.ButtonRight.pressing() ||
        Controller.ButtonL1.pressing() || Controller.ButtonL2.pressing() ||
        Controller.ButtonR1.pressing() || Controller.ButtonR2.pressing() ||
        Brain.Screen.pressing()) {
      dismissed = true;
      break;
    } else {
      this_thread::sleep_for(100);
    }
  }
}

void checkDevices() {
  bool noErrors = true;

  for (auto &i : devicesList) {
    if (!i.device->installed()) {
      error(&i);
      noErrors = false;
    }
  }

  if (noErrors) {
    dismissed = false;
  }
}