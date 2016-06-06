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
  return  {{0,0}, shipLength, shipLength, true};
}

inline bool BAShipIsShipDestroyed(BAShip ship){
  return ship.remainingLength <= 0;
}

#endif
