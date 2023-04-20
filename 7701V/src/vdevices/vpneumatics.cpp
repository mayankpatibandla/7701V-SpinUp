#include "vdevices/vpneumatics.hpp"

vdevices::togglepneumatics::togglepneumatics(triport::port &port)
    : vex::pneumatics(port){};

void vdevices::togglepneumatics::toggle() { set(!value()); }