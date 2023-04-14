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
                    ? "BLUE"
                    : redMax > leftRollerOptical.hue() ||
                              leftRollerOptical.hue() > redMin
                          ? "RED"
                          : leftRollerOptical.color() == transparent ? "TRAN"
                                                                     : "OTHR");
  Brain.Screen.printAt(240, 160, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  Brain.Screen.setPenColor(rightRollerOptical.hue());
  strstream << "R Col: "
            << (blueMax > rightRollerOptical.hue() &&
                        rightRollerOptical.hue() > blueMin
                    ? "BLUE"
                    : redMax > rightRollerOptical.hue() ||
                              rightRollerOptical.hue() > redMin
                          ? "RED"
                          : rightRollerOptical.color() == transparent
                                ? "TRAN"
                                : "OTHR");
  Brain.Screen.printAt(360, 160, strstream.str().c_str());
  strstream.str("");
  strstream.clear();

  Brain.Screen.setPenColor(
      rollerColor == red ? red : rollerColor == blue ? blue : white);
  strstream << "Target Color: "
            << (rollerColor == red ? "RED"
                                   : rollerColor == blue ? "BLUE" : "OTHER");
  Brain.Screen.printAt(240, 180, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
}