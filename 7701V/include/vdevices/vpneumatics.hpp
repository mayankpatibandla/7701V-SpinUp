#pragma once
#include "vex/vex.hpp"

namespace vdevices {
class togglepneumatics : public vex::pneumatics {
public:
  togglepneumatics(triport::port &port);

  void toggle();
};
} // namespace vdevices