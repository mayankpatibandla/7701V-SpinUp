#pragma once
#include "vex.h"

namespace vdevices {
class togglepneumatics : public vex::pneumatics {
public:
  togglepneumatics(triport::port &port);

  void toggle();
};
} // namespace vdevices