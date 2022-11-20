#include "odom.h"

vex::thread positiontracking_thread;

void odomInit() {
  positiontracking_thread = vex::thread(positiontracking::positiontracking);
}