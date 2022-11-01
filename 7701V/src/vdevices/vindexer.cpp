#include "vdevices/vindexer.h"

//TODO: add threaded autofire

void vdevices::indexer::setShooting(bool value){
  isShooting = value;
}

bool vdevices::indexer::getShooting(){
  return isShooting;
}

void vdevices::indexer::startShooting(){isShooting = true;}
void vdevices::indexer::stopShooting(){isShooting = false;}

void vdevices::indexer::shootDisc(){
  set(true);
  this_thread::sleep_for(100);
  
  set(false);
}