#include "gui.h"

void printOptical() {
  std::ostringstream strstream;
  strstream.clear();

  Brain.Screen.setFillColor(transparent);

  color leftCol;
  leftCol = leftCol.hsv(leftRollerOptical.hue(), 1, 1);
  color rightCol;
  rightCol = rightCol.hsv(rightRollerOptical.hue(), 1, 1);

  Brain.Screen.setPenColor(leftCol);
  Brain.Screen.printAt(240, 120, "L Hue: %03.0f", leftRollerOptical.hue());
  Brain.Screen.printAt(240, 140, "L Bri: %03.1f",
                       leftRollerOptical.brightness());
  Brain.Screen.setPenColor(rightCol);
  Brain.Screen.printAt(370, 120, "R Hue: %03.0f", rightRollerOptical.hue());
  Brain.Screen.printAt(370, 140, "R Bri: %03.1f",
                       rightRollerOptical.brightness());

  Brain.Screen.setPenColor(leftCol);
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

  Brain.Screen.setPenColor(rightCol);
  strstream << "R Col: "
            << (blueMax > rightRollerOptical.hue() &&
                        rightRollerOptical.hue() > blueMin
                    ? "Blue"
                    : redMax > rightRollerOptical.hue() ||
                              rightRollerOptical.hue() > redMin
                          ? "Red"
                          : rightRollerOptical.color() == transparent ? "Tran"
                                                                      : "Othr");
  Brain.Screen.printAt(370, 160, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  Brain.Screen.setPenColor(white);
  strstream << "L Obj: " << (leftRollerOptical.isNearObject() ? "Yes" : "No");
  Brain.Screen.printAt(240, 180, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
  strstream << "R Obj: " << (rightRollerOptical.isNearObject() ? "Yes" : "No");
  Brain.Screen.printAt(370, 180, strstream.str().c_str());

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