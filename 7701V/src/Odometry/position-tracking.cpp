#include "odom.h"

namespace positiontracking {
bool usingInertial = false;

// radius of tracking wheel (in inches)
const double WHEEL_RADIUS = 1.4; // 2.75 in
// circumference of tracking wheel (in inches)
const double WHEEL_CIRCUMFERENCE = M_TWOPI * WHEEL_RADIUS;

// left-right distance between left and right tracking wheels and tracking
// center (in inches)
const double s_L = 0;
const double s_R = 0;
// forward-backward distance between back tracking wheel and tracking center (in
// inches)
const double s_S = 0;

double pos_x;     // x position of robot (in inches)
double pos_y;     // y position of robot (in inches)
double pos_theta; // angle of robot's heading (in radians)

// main position tracking function, will be used in its own thread
void positionTracking() {
  // previous position of encoders: L = left, R = right, S = back
  double encL_0 = 0, encR_0 = 0, encS_0 = 0;

  // previous positions of robot: theta = heading angle (in radians), x & y =
  // position (in inches)
  double theta_0 = 0, d_0_x = 0, d_0_y = 0;

  while (true) {
    uint32_t timeStart = Brain.Timer.system();
    // encoder sensor readings (in degrees)
    double encL = lRot.position(deg);
    double encR = rRot.position(deg);
    double encS = sRot.position(deg);

    // Change in position for each tracking wheel
    // Equation is circumference of wheel times section of circle where the
    // encoder's angle changed: delta = circumference * deltaEnc / 360
    double delta_L = WHEEL_CIRCUMFERENCE * (encL - encL_0) / 360;
    double delta_R = WHEEL_CIRCUMFERENCE * (encR - encR_0) / 360;
    double delta_S = WHEEL_CIRCUMFERENCE * (encS - encS_0) / 360;

    // set previous encoder angles to current ones for use in next loop cycle
    encL_0 = encL;
    encR_0 = encR;
    encS_0 = encS;

    double theta_1, delta_theta;
    // get robot heading from inertial sensor and convert it from degrees to
    // radians
    if (usingInertial) {
      theta_1 = -inert.rotation(deg) * M_PI / 180;
      delta_theta = theta_1 - theta_0;
    }
    // get robot heading from tracking wheels instead because it is more
    // accurate
    else {
      delta_theta = (delta_L - delta_R) / (s_L + s_R);
      theta_1 = delta_theta + theta_0;
    }

    // change in local position
    double delta_d_l_x = 0, delta_d_l_y = 0;
    // if delta theta is 0, set change in local position to delta s and delta r
    // this avoids a divide by zero error
    if (delta_theta == 0) {
      delta_d_l_x = delta_S;
      delta_d_l_y = delta_R;
    } else { // otherwise set it to this:
      delta_d_l_x =
          2 * std::sin(delta_theta / 2) * (delta_S / delta_theta + s_S);
      delta_d_l_y =
          2 * std::sin(delta_theta / 2) * (delta_L / delta_theta - s_L);
    }

    // calculate average orientation
    double theta_m = theta_0 + delta_theta / 2;

    // convert change in local position to polar coords so we can rotate it
    double pl_r = std::hypot(delta_d_l_x, delta_d_l_y);
    double pl_theta = std::atan2(delta_d_l_y, delta_d_l_x);

    // rotate the theta of the polar coord by -theta_m
    pl_theta -= theta_m;

    // convert back to rectangular coords to find change in position
    double delta_d_x = pl_r * std::cos(pl_theta);
    double delta_d_y = pl_r * std::sin(pl_theta);

    // set global position to previous pos + change in pos
    double d_1_x = d_0_x + delta_d_x;
    double d_1_y = d_0_y + delta_d_y;

    // set previous positions as current positions for use in next loop cycle
    d_0_x = d_1_x;
    d_0_y = d_1_y;
    theta_0 = theta_1;

    // assign the global positions to the vars located outside the function so
    // they can be used elsewhere
    pos_x = d_1_x;
    pos_y = d_1_y;
    pos_theta = theta_1;

    // sleep this thread for 15 milliseconds to conserve power and get more
    // precision
    this_thread::sleep_until(timeStart + 10);
  }
}

// functions that can be used externally to get the positions
double x() { return pos_y; }
double y() { return pos_x; }
double theta() { return pos_theta; }

// returns angle with wrapping
// range ? [-pi, pi) : [0, 2pi)
double thetaWrapped(bool range) {
  //-pi to pi
  if (range) {
    double temp_theta = fmod(theta() + M_PI, 2 * M_PI);
    if (temp_theta < 0)
      temp_theta += 2 * M_PI;
    return temp_theta - M_PI;
  }
  // 0 to 2pi
  double temp_theta = fmod(theta(), 2 * M_PI);
  if (temp_theta < 0)
    temp_theta += 2 * M_PI;
  return temp_theta;
}

double plrR() { return std::hypot(x(), y()); }
double plrTheta() { return std::atan2(y(), x()); }
} // namespace positiontracking