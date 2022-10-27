#include "vdevices/vpneumatics.h"

vdevices::togglepneumatics::togglepneumatics(triport::port &port)
    : vex::pneumatics(port){};

void vdevices::togglepneumatics::toggle() { set(!value()); }