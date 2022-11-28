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
  return {pose.x * k + 20, pose.y * k + 220, pose.theta}; // theta?
}

Pose rotatePose(Pose pose, Pose c) {
  double x =
      (pose.x * std::cos(pose.theta) - pose.y * std::sin(pose.theta)) + c.x;
  double y =
      (pose.y * std::cos(pose.theta) + pose.x * std::sin(pose.theta)) + c.y;

  return {x, y, pose.theta};
}

void drawRobot() {
  Pose pose = worldToScreen(pt::pose());

  Brain.Screen.printAt(240, 130, "Pose X: %5f", pose.x);
  Brain.Screen.printAt(240, 150, "Pose Y: %5f", pose.y);
  Brain.Screen.printAt(240, 170, "Pose Theta: %5f", pose.theta);

  Brain.Screen.setPenColor(green);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawCircle(pose.x, pose.y, 2);
  Brain.Screen.drawLine(pose.x - 5, pose.y + 5, pose.x, pose.y - 5);
  Brain.Screen.drawLine(pose.x + 5, pose.y + 5, pose.x, pose.y - 5);
  Brain.Screen.setPenColor(purple);
  Brain.Screen.setFillColor(purple);
  Pose rotPose = rotatePose({pose.x, pose.y - 5, pose.theta}, pose);
  Brain.Screen.drawLine(pose.x - 5, pose.y + 5, rotPose.x, rotPose.y);
  Brain.Screen.drawLine(pose.x + 5, pose.y + 5, rotPose.x, rotPose.y);

  // Pose rotPose = rotatePose(pose, {pose.x - 20, pose.y - 20, pose.theta});

  // Brain.Screen.setPenColor(white);
  // Brain.Screen.setFillColor(transparent);
  // Brain.Screen.printAt(240, 200, "Pose X: %5f", rotPose.x);
  // Brain.Screen.printAt(240, 220, "Pose Y: %5f", rotPose.y);
  // Brain.Screen.printAt(240, 240, "Pose Theta: %5f", pose.theta);

  // Brain.Screen.setPenColor(purple);
  // Brain.Screen.setFillColor(purple);
  // Brain.Screen.drawCircle(rotPose.x, rotPose.y, 3);
}