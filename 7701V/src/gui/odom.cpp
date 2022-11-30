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

Pose worldToScreen(Pose pose, Pose offset) {
  const double k = 200.0 / 140.02;
  return {pose.x * k + offset.x, pose.y * k + offset.y, pose.theta}; // theta?
}

Pose rotatePose(Pose pose, Pose c) {
  // double x =
  //     (pose.x * std::cos(pose.theta) - pose.y * std::sin(pose.theta)) + c.x;
  // double y =
  //     (pose.y * std::cos(pose.theta) + pose.x * std::sin(pose.theta)) + c.y;

  double x = ((pose.x - c.x) * std::cos(pose.theta) +
              (pose.y - c.y) * std::sin(pose.theta)) +
             c.x;
  double y = (-(pose.x - c.x) * std::sin(pose.theta) +
              (pose.y - c.y) * std::cos(pose.theta)) +
             c.y;

  return {x, y, pose.theta};
}

void drawRobot() {
  // Brain.Screen.printAt(240, 130, "Pose X: %5f", pose.x);
  // Brain.Screen.printAt(240, 150, "Pose Y: %5f", pose.y);
  // Brain.Screen.printAt(240, 170, "Pose Theta: %5f", pose.theta);

  Pose pose = worldToScreen(pt::pose(), {20, 220, 0});
  Pose rotPose0 = rotatePose({pose.x, pose.y - 5, pose.theta}, pose);
  Pose rotPose1 = rotatePose({pose.x - 5, pose.y + 5, pose.theta}, pose);
  Pose rotPose2 = rotatePose({pose.x + 5, pose.y + 5, pose.theta}, pose);

  Brain.Screen.setPenColor(green);
  Brain.Screen.setFillColor(green);
  Brain.Screen.drawCircle(pose.x, pose.y, 2);
  Brain.Screen.drawLine(rotPose1.x, rotPose1.y, rotPose0.x, rotPose0.y);
  Brain.Screen.drawLine(rotPose2.x, rotPose2.y, rotPose0.x, rotPose0.y);
}