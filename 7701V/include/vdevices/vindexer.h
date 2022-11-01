#pragma once
#include "vdevices/vpneumatics.h"

namespace vdevices{
class indexer : public togglepneumatics{
protected:
  bool isShooting;

public:
  void setShooting(bool value);
  bool getShooting();

  void startShooting();
  void stopShooting();

  void shootDisc();
};
}