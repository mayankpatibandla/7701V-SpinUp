#include "gui.h"

void printOptical() {
  std::ostringstream strstream;
  strstream.clear();

  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(leftRollerOptical.color());
  // TODO: use both optical sensors
  Brain.Screen.printAt(240, 120, "Optical Hue: %8f", leftRollerOptical.hue());
  strstream << "Optical Color: "
            << (blueMax > leftRollerOptical.hue() &&
                        leftRollerOptical.hue() > blueMin
                    ? "BLUE"
                    : redMax > leftRollerOptical.hue() ||
                              leftRollerOptical.hue() > redMin
                          ? "RED"
                          : leftRollerOptical.color() == transparent
                                ? "TRANSPARENT"
                                : "OTHER");
  Brain.Screen.printAt(240, 140, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
  Brain.Screen.setPenColor(white);
  strstream << "Target Color: "
            << (rollerColor == red ? "RED"
                                   : rollerColor == blue ? "BLUE" : "OTHER");
  Brain.Screen.printAt(240, 160, strstream.str().c_str());
  strstream.str("");
  strstream.clear();
}