#include "control/control.hpp"

void autons::test() {
  turnToAngle(M_PI, 0, 1000, 1, {0.5, 0, 0});
  std::cout << "Theta (rad): " << pt::thetaWrapped() << std::endl;
}