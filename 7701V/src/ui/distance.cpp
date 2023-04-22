#include "ui/gui.hpp"

void printDistance() {
  double dist = storageDistance.objectDistance(mm);

  Brain.Screen.setFillColor(transparent);
  if (storageDistMin < storageDistance.objectDistance(mm) &&
      storageDistance.objectDistance(mm) < storageDistMax) {
    Brain.Screen.setPenColor(yellow);
  } else {
    Brain.Screen.setPenColor(white);
  }
  Brain.Screen.printAt(240, 230, "Distance: %3f mm", dist);
}