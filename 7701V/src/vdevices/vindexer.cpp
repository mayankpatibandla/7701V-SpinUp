#include "vdevices/vindexer.h"

#include "robot-config.h" // for debug, remove later

vdevices::indexer::indexer(triport::port &port, uint32_t shotCooldown, uint32_t autofireCooldown)
    : togglepneumatics(port), shotCooldown(shotCooldown), autofireCooldown(autofireCooldown) {
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
      this_thread::sleep_for(instance->getShotCooldown());
    } else {
      this_thread::sleep_for(50);
    }
    //TODO: fix this
    
    // Controller.Screen.print("in autofire");
  }
}

uint32_t vdevices::indexer::getShotCooldown() { return shotCooldown; }
void vdevices::indexer::setShotCooldown(uint32_t value) {
  shotCooldown = value;
}

bool vdevices::indexer::getShooting() { return isShooting; }
void vdevices::indexer::setShooting(bool value) { isShooting = value; }

void vdevices::indexer::startShooting() { isShooting = true; }
void vdevices::indexer::stopShooting() { isShooting = false; }

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