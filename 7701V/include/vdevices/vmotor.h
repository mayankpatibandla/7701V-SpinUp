#pragma once
#include "vex.h"

namespace vdevices {
class togglemotor : public vex::motor {
private:
  bool state;

protected:
  togglemotor();

public:
  togglemotor(int32_t index, vex::gearSetting gears, bool reverse);

  bool getState();
  void setState(bool value);
  void toggleState();
};

class togglemotor_group : public togglemotor, public vex::motor_group {
public:
  using vex::motor_group::motor_group;
  using vex::motor_group::spin;
};
} // namespace vmotor