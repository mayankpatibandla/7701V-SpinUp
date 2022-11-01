#pragma once
#include "vex.h"

namespace vdevices {
class togglepneumatics : public vex::pneumatics {
public:

  void toggle();
};
} // namespace vdevices