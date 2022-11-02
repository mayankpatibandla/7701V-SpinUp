#include "vdevices/vindexer.h"

#include "robot-config.h" // for debug, remove later

vdevices::indexer::indexer(triport::port &port, uint32_t shotCooldown,
                           uint32_t autofireCooldown)
    : togglepneumatics(port), shotCooldown(shotCooldown),
      autofireCooldown(autofireCooldown) {
  autofireThread = vex::thread(autofire, static_cast<void *>(this));
}

// function does not work
void vdevices::indexer::autofire(void *arg) {
  if (arg == NULL) {
    return;
  }
  indexer *instance = static_cast<indexer *>(arg);

  while (true) {
    if (instance->getAutofiring()) {
      instance->shootDisc();
    }
    this_thread::sleep_for(instance->getAutofireCooldown());
    // TODO: fix this

    // Controller.Screen.print("in autofire");
  }
}

uint32_t vdevices::indexer::getShotCooldown() { return shotCooldown; }
void vdevices::indexer::setShotCooldown(uint32_t value) {
  shotCooldown = value;
}

uint32_t vdevices::indexer::getAutofireCooldown() { return autofireCooldown; }
void vdevices::indexer::setAutofireCooldown(uint32_t value) {
  autofireCooldown = value;
}

bool vdevices::indexer::getAutofiring() { return isAutofiring; }
void vdevices::indexer::setAutofiring(bool value) { isAutofiring = value; }

void vdevices::indexer::startAutofiring() { setAutofiring(true); }
void vdevices::indexer::stopAutofiring() { setAutofiring(false); }

void vdevices::indexer::shootDisc() {
  set(true);
  this_thread::sleep_for(shotCooldown);
  set(false);
}

void vdevices::indexer::shootDisc(uint32_t cooldown) {
  set(true);
  this_thread::sleep_for(cooldown);
  set(false);
}