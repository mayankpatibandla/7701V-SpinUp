#pragma once
#include "vdevices/vmotor.hpp"

namespace vdevices {
class flywheel : public togglemotor, public vex::motor_group {
public:
  struct PID {
    double kP, kI, kD, threshold, kP2, maxError, dT;

    PID(double kP = 0, double kI = 0, double kD = 0, double threshold = 0,
        double kP2 = 0, double maxError = 0, double dT = 15);
  };

protected:
  PID pid;

  double targetVel = 0.0;

  vex::thread pidThread;
  static void pidCore(void *arg);

public:
  using vex::motor_group::motor_group;
  using vex::motor_group::spin;
  using vex::motor_group::stop;
  using vex::motor_group::velocity;

  void init();

  PID getPID();
  void setPID(PID pid_a);

  double getTargetVelocity();
  void setTargetVelocity(double target);
};
} // namespace vdevices