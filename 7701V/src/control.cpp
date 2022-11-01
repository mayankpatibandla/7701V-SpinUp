#include "control.h"

void shootDisc() {
  indexerSlnd.set(true);
  this_thread::sleep_for(100);
  indexerSlnd.set(false);
}