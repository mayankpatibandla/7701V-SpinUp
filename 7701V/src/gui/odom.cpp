#include "gui.h"

void printOdom() {
  Brain.Screen.setPenWidth(2);
  Brain.Screen.setPenColor(color(0xFF, 0xFF, 0xFF));
  Brain.Screen.setFillColor(transparent);
  Brain.Screen.setFont(mono20);

  Brain.Screen.printAt(240, 30, "Pos X  (in): %5f", pt::x());
  Brain.Screen.printAt(240, 50, "Pos Y  (in): %5f", pt::y());
  Brain.Screen.printAt(240, 70, "Theta (rad): %5f", pt::thetaWrapped());
  Brain.Screen.printAt(240, 90, "Theta (deg): %5f",
                       pt::thetaWrapped() * 180 / M_PI);
}

Pose worldToScreen(Pose pose) {
  const double k = 200.0 / 140.02;
  return {pose.x * k + 20, pose.y * k + 20, pose.theta}; // theta?
}

void drawRobot() {
  Pose pose = worldToScreen(pt::pose());

  Brain.Screen.printAt(240, 130, "Pose: %3f, %3f, %3f", pose.x, pose.y, pose.theta);

  Brain.Screen.setPenColor(green);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawCircle(pose.x, pose.y, 3);
}