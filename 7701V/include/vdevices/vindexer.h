#pragma once
#include "vdevices/vpneumatics.h"

//todo:
namespace vdevices{
class indexer : public togglepneumatics{
protected:
  bool x;
};
}