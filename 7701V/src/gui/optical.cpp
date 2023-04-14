#include "gui.h"

void printOptical() {
  std::ostringstream strstream;
  strstream.clear();

  Brain.Screen.setFillColor(transparent);

  Brain.Screen.setPenColor(leftRollerOptical.hue());
  Brain.Screen.printAt(240, 120, "L Hue: %3f", leftRollerOptical.hue());
  Brain.Screen.printAt(240, 140, "L Bri: %3f", leftRollerOptical.brightness());
  Brain.Screen.setPenColor(rightRollerOptical.hue());
  Brain.Screen.printAt(350, 120, "R Hue: %3f", rightRollerOptical.hue());
  Brain.Screen.printAt(350, 140, "R Bri: %3f", rightRollerOptical.brightness());

  Brain.Screen.setPenColor(leftRollerOptical.hue());
  strstream << "L Col: "
            << (blueMax > leftRollerOptical.hue() &&
                        leftRollerOptical.hue() > blueMin
                    ? "Blue"
                    : redMax > leftRollerOptical.hue() ||
                              leftRollerOptical.hue() > redMin
                          ? "Red"
                          : leftRollerOptical.color() == transparent ? "Tran"
                                                                     : "Othr");
  Brain.Screen.printAt(240, 160, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  Brain.Screen.setPenColor(rightRollerOptical.hue());
  strstream << "R Col: "
            << (blueMax > rightRollerOptical.hue() &&
                        rightRollerOptical.hue() > blueMin
                    ? "Blue"
                    : redMax > rightRollerOptical.hue() ||
                              rightRollerOptical.hue() > redMin
                          ? "Red"
                          : rightRollerOptical.color() == transparent ? "Tran"
                                                                      : "Othr");
  Brain.Screen.printAt(360, 160, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  Brain.Screen.setPenColor(white);
  strstream << "L Obj: " << (leftRollerOptical.isNearObject() ? "Yes" : "No")
            << "R Obj: " << (rightRollerOptical.isNearObject() ? "Yes" : "No");
  Brain.Screen.printAt(240, 180, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  Brain.Screen.setPenColor(
      rollerColor == red ? red : rollerColor == blue ? blue : white);
  strstream << "Target Color: "
            << (rollerColor == red ? "Red"
                                   : rollerColor == blue ? "Blue" : "Other");
  Brain.Screen.printAt(240, 200, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
}