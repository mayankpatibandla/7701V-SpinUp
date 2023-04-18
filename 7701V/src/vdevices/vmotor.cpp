#include "vdevices/vmotor.hpp"

vdevices::togglemotor::togglemotor() : vex::motor(-1) {}
vdevices::togglemotor::togglemotor(int32_t index, vex::gearSetting gears,
                                   bool reverse)
    : vex::motor(index, gears, reverse) {}

bool vdevices::togglemotor::getState() { return state; }
void vdevices::togglemotor::setState(bool value) { state = value; }
void vdevices::togglemotor::toggleState() { setState(!getState()); }