#ifndef BASHIP_H
#define BASHIP_H
#include <Arduboy.h>
#include "ABGeometry.h"

struct BAShip{
  ABPoint position;
  byte fullLength;
  byte remainingLength;
  bool horizontal;
};

inline BAShip BAShipMake(byte shipLength){
  return  {shipLength, shipLength, true};
}

inline bool isShipDestroyed(BAShip ship){
  return ship.remainingLength <= 0;
}

#endif
