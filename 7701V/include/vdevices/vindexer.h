#pragma once
#include "vdevices/vpneumatics.h"

namespace vdevices {
class indexer : public togglepneumatics {
protected:
  uint32_t shotCooldown;

  bool isAutofiring;
  uint32_t autofireCooldown;

  // threaded class members:
  // https://www.vexforum.com/t/creating-a-task-using-a-non-static-class-function/82721/2?u=xtigr
  vex::thread autofireThread;
  static void autofire(void *arg);

public:
  indexer(triport::port &port, uint32_t shotCooldown,
          uint32_t autofireCooldown);

  uint32_t getShotCooldown();
  void setShotCooldown(uint32_t value);

  bool getAutofiring();
  void setAutofiring(bool value);

  uint32_t getAutofireCooldown();
  void setAutofiringCooldown(uint32_t value);

  void startShooting();
  void stopShooting();

  void shootDisc();
  void shootDisc(uint32_t cooldown);
};
} // namespace vdevices