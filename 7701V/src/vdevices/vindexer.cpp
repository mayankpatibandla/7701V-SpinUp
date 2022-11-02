#include "vdevices/vindexer.h"

vdevices::indexer::indexer(triport::port &port, uint32_t shotCooldown)
    : togglepneumatics(port), shotCooldown(shotCooldown) {
  autofireThread = vex::thread(autofire, static_cast<void *>(this));
}

void vdevices::indexer::autofire(void *arg) {
  if (arg == NULL) {
    return;
  }
  indexer *instance = static_cast<indexer *>(arg);

  if (instance->isShooting) {
    instance->shootDisc(instance->shotCooldown);
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