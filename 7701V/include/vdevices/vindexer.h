#pragma once
#include "vdevices/vpneumatics.h"

namespace vdevices {
class indexer : public togglepneumatics {
protected:
  uint32_t shotCooldown;

  uint32_t autofireCooldown;
  bool isAutofiring;

  // threaded class members:
  // https://www.vexforum.com/t/creating-a-task-using-a-non-static-class-function/82721/2?u=xtigr
  vex::thread autofireThread;
  static void autofire(void *arg);

public:
  indexer(triport::port &port, uint32_t shotCooldown,
          uint32_t autofireCooldown);

  uint32_t getShotCooldown();
  void setShotCooldown(uint32_t value);

  uint32_t getAutofireCooldown();
  void setAutofireCooldown(uint32_t value);

  bool getAutofiring();
  void setAutofiring(bool value);

  void startAutofiring();
  void stopAutofiring();

  void shootDisc();
  void shootDisc(uint32_t cooldown);
};
} // namespace vdevices