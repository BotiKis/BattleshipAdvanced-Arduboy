#ifndef BASHIP_H
#define BASHIP_H
#include <Arduboy.h>

typedef enum BAShipType{
  BAShipTypeSmall = 1,
  BAShipTypeMedium,
  BAShipTypeBig
}BAShipType;

struct BAShip{
  BAShipType shipType;
  byte fullLength;
  byte remainingLength;
  bool horizontal;
};

inline BAShip BAShipMake(BAShipType shipType, byte shipLength){
  return  {shipType, shipLength, shipLength, true};
}

inline bool isShipDestroyed(BAShip ship){
  return ship.remainingLength <= 0;
}

#endif
