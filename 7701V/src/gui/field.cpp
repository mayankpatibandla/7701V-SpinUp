#include "gui.h"

void drawField() {
  // border
  Brain.Screen.setPenWidth(4);
  Brain.Screen.setPenColor(color(0xE1, 0xD9, 0xD1));
  Brain.Screen.setFillColor(color(0xC0, 0xC0, 0xC0));
  Brain.Screen.drawRectangle(18, 18, 202, 202);
  Brain.Screen.setPenWidth(2);

  // tiles
  Brain.Screen.setPenColor(color(0xD0, 0xD0, 0xD0));
  Brain.Screen.setFillColor(color(0xD0, 0xD0, 0xD0));
  double tileInterval = 100. / 3.;
  for (int i = 1; i < 6; i++) {
    Brain.Screen.drawLine(i * tileInterval + 20, 20, i * tileInterval + 20,
                          220);
    Brain.Screen.drawLine(20, i * tileInterval + 20, 220,
                          i * tileInterval + 20);
  }

  // tape
  Brain.Screen.setPenColor(color(0xFF, 0xFF, 0xFF));
  Brain.Screen.setFillColor(transparent);
  {
    // auton line
    Brain.Screen.drawLine(20, 23, 217, 220);
    Brain.Screen.drawLine(23, 20, 220, 217);

    // blue low goal
    Brain.Screen.drawLine(153, 20, 153, 53);
    Brain.Screen.drawLine(220, 87, 187, 87);

    // red low goal
    Brain.Screen.drawLine(87, 220, 87, 187);
    Brain.Screen.drawLine(20, 153, 53, 153);
  }

  // blue barrier
  Brain.Screen.setPenColor(color(0x00, 0x00, 0xFF));
  Brain.Screen.drawLine(153, 53, 153, 87);
  Brain.Screen.drawLine(187, 87, 153, 87);

  // red barrier
  Brain.Screen.setPenColor(color(0xFF, 0x00, 0x00));
  Brain.Screen.drawLine(87, 187, 87, 153);
  Brain.Screen.drawLine(53, 153, 87, 153);

  // red high goal
  {
    // black support
    Brain.Screen.setPenColor(color(0x00, 0x00, 0x00));
    Brain.Screen.drawLine(220, 20, 195, 45);

    // white support
    Brain.Screen.setPenColor(color(0xFF, 0xFF, 0xFF));
    Brain.Screen.drawLine(171, 20, 220, 69);

    // goal
    Brain.Screen.setPenColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.drawCircle(195, 45, 11);
  }

  // blue high goal
  {
    // black support
    Brain.Screen.setPenColor(color(0x00, 0x00, 0x00));
    Brain.Screen.drawLine(20, 220, 45, 195);

    // white support
    Brain.Screen.setPenColor(color(0xFF, 0xFF, 0xFF));
    Brain.Screen.drawLine(20, 171, 69, 220);

    // goal
    Brain.Screen.setPenColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.drawCircle(45, 195, 11);
  }

  // discs
  {
    Brain.Screen.setPenColor(color(0xE5, 0xB8, 0x00));
    Brain.Screen.setFillColor(color(0xE5, 0xB8, 0x00));

    // auton line
    Brain.Screen.drawCircle(36, 36, 4);
    Brain.Screen.drawCircle(53, 53, 4);
    Brain.Screen.drawCircle(70, 70, 4);
    Brain.Screen.drawCircle(87, 87, 4);
    Brain.Screen.drawCircle(103, 103, 4);

    Brain.Screen.drawCircle(137, 137, 4);
    Brain.Screen.drawCircle(154, 154, 4);
    Brain.Screen.drawCircle(170, 170, 4);
    Brain.Screen.drawCircle(188, 188, 4);
    Brain.Screen.drawCircle(204, 204, 4);

    // blue side
    Brain.Screen.drawCircle(103, 70, 4);
    Brain.Screen.drawCircle(120, 87, 4);
    Brain.Screen.drawCircle(137, 103, 4);
    Brain.Screen.drawCircle(168, 137, 4);

    // red side
    Brain.Screen.drawCircle(70, 103, 4);
    Brain.Screen.drawCircle(103, 137, 4);
    Brain.Screen.drawCircle(120, 154, 4);
    Brain.Screen.drawCircle(137, 168, 4);

    // blue low goal
    Brain.Screen.drawCircle(147, 57, 4);
    Brain.Screen.drawCircle(147, 70, 4);
    Brain.Screen.drawCircle(147, 83, 4);

    Brain.Screen.drawCircle(157, 92, 4);
    Brain.Screen.drawCircle(170, 92, 4);
    Brain.Screen.drawCircle(182, 92, 4);

    // red low goal
    Brain.Screen.drawCircle(57, 146, 4);
    Brain.Screen.drawCircle(70, 146, 4);
    Brain.Screen.drawCircle(83, 146, 4);

    Brain.Screen.drawCircle(92, 157, 4);
    Brain.Screen.drawCircle(92, 169, 4);
    Brain.Screen.drawCircle(92, 182, 4);
  }

  // rollers
  Brain.Screen.setPenWidth(1);
  {
    // red bottom right
    Brain.Screen.setPenColor(color(0x00, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0x00));
    Brain.Screen.drawRectangle(168, 216, 2, 4);
    Brain.Screen.drawRectangle(184, 216, 2, 4);
    Brain.Screen.setPenColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.drawRectangle(170, 216, 14, 2);
    Brain.Screen.setPenColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.drawRectangle(170, 218, 14, 2);

    // blue bottom right
    Brain.Screen.setPenColor(color(0x00, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0x00));
    Brain.Screen.drawRectangle(216, 168, 4, 2);
    Brain.Screen.drawRectangle(216, 184, 4, 2);
    Brain.Screen.setPenColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.drawRectangle(218, 170, 2, 14);
    Brain.Screen.setPenColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.drawRectangle(216, 170, 2, 14);

    // blue top left
    Brain.Screen.setPenColor(color(0x00, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0x00));
    Brain.Screen.drawRectangle(55, 20, 2, 4);
    Brain.Screen.drawRectangle(71, 20, 2, 4);
    Brain.Screen.setPenColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.drawRectangle(57, 20, 14, 2);
    Brain.Screen.setPenColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.drawRectangle(57, 22, 14, 2);

    // red top left
    Brain.Screen.setPenColor(color(0x00, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0x00));
    Brain.Screen.drawRectangle(20, 55, 4, 2);
    Brain.Screen.drawRectangle(20, 71, 4, 2);
    Brain.Screen.setPenColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.setFillColor(color(0xFF, 0x00, 0x00));
    Brain.Screen.drawRectangle(22, 57, 2, 14);
    Brain.Screen.setPenColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.setFillColor(color(0x00, 0x00, 0xFF));
    Brain.Screen.drawRectangle(20, 57, 2, 14);
  }

  // loaders
  Brain.Screen.setPenColor(color(0x3A, 0x3A, 0x3A));
  Brain.Screen.setFillColor(color(0x3A, 0x3A, 0x3A));
  Brain.Screen.drawRectangle(15, 114, 5, 12);
  Brain.Screen.drawRectangle(220, 114, 5, 12);

  // nets
  Brain.Screen.setPenColor(color(0x00, 0x00, 0x00));
  Brain.Screen.setFillColor(color(0x00, 0x00, 0x00));
  Brain.Screen.drawRectangle(137, 19, 83, 4);
  Brain.Screen.drawRectangle(217, 19, 4, 83);

  Brain.Screen.drawRectangle(19, 217, 83, 4);
  Brain.Screen.drawRectangle(19, 137, 4, 83);
}