#include "odom.h"
#include "gui.h"

void printOdom() {
  Brain.Screen.setPenWidth(2);
  Brain.Screen.setPenColor(color(0xFF, 0xFF, 0xFF));
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setFont(mono20);

  Brain.Screen.printAt(240, 30, "Pos X  (in): %5f", pt::x());
  Brain.Screen.printAt(240, 55, "Pos Y  (in): %5f", pt::y());
  Brain.Screen.printAt(240, 80, "Theta (rad): %5f", pt::thetaWrapped());
  Brain.Screen.printAt(240, 105, "Theta (deg): %5f",
                       pt::thetaWrapped() * 180 / M_PI);
}

void worldToScreen(double x, double y, double theta){
  
}