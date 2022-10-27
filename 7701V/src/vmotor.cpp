#include "vmotor.h"

vmotor::togglemotor::togglemotor() : vex::motor(-1) {}
vmotor::togglemotor::togglemotor(int32_t index, vex::gearSetting gears,
                                 bool reverse)
    : vex::motor(index, gears, reverse) {}

bool vmotor::togglemotor::getState() { return state; }
void vmotor::togglemotor::setState(bool value) { state = value; }
void vmotor::togglemotor::toggleState() { setState(!getState()); }

vmotor::togglemotor_group::togglemotor_group(vmotor::togglemotor &m,
                                             vmotor::togglemotor &...)
    : vex::motor_group(m) {}