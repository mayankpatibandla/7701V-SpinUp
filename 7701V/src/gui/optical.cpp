#include "gui.h"

void printOptical() {
  std::ostringstream strstream;
  strstream.clear();

  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setPenColor(rollerOptical.color());

  Brain.Screen.printAt(240, 120, "Optical Hue: %8f", rollerOptical.hue());
  strstream << "Optical Color: "
            << (rollerOptical.color() == blue
                    ? "BLUE"
                    : rollerOptical.color() == red
                          ? "RED"
                          : rollerOptical.color() == transparent ? "TRANSPARENT"
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