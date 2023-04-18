#include "gui.hpp"

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

Pose rotatePose(Pose pose, Pose c) {
  double x = ((pose.x - c.x) * std::cos(pose.theta) +
              (pose.y - c.y) * std::sin(pose.theta)) +
             c.x;
  double y = (-(pose.x - c.x) * std::sin(pose.theta) +
              (pose.y - c.y) * std::cos(pose.theta)) +
             c.y;

  return {x, y, pose.theta};
}

Pose worldToScreen(Pose pose, Pose offset) {
  // field side length (pixels) / field side length (inches)
  const double k = 200.0 / 140.02;

  // rotate the pose to account for starting position
  // subtract pi/2 to account for odom x-axis being forward
  Pose rotPose = rotatePose(
      {pose.x * k + offset.x, pose.y * k + offset.y, offset.theta - M_PI_2},
      {120, 120, 0}); // c = field center

  return {rotPose.x, rotPose.y, pose.theta + offset.theta};
}

void drawRobot(Pose offset) {
  // reversed x because screen coord system x-axis is opposite field x-axis
  Pose pose = worldToScreen({-pt::x(), pt::y(), pt::thetaWrapped()}, offset);

  Pose rotPose0 = rotatePose({pose.x, pose.y - 5, pose.theta}, pose);
  Pose rotPose1 = rotatePose({pose.x - 5, pose.y + 5, pose.theta}, pose);
  Pose rotPose2 = rotatePose({pose.x + 5, pose.y + 5, pose.theta}, pose);

  Brain.Screen.setPenColor(green);
  Brain.Screen.setFillColor(green);
  Brain.Screen.setPenWidth(1);
  Brain.Screen.drawCircle(pose.x, pose.y, 2);
  Brain.Screen.setPenWidth(3);
  Brain.Screen.drawLine(rotPose1.x, rotPose1.y, rotPose0.x, rotPose0.y);
  Brain.Screen.drawLine(rotPose2.x, rotPose2.y, rotPose0.x, rotPose0.y);
}