#ifndef BASHIP_H
#define BASHIP_H
#include <Arduboy2.h>

typedef enum BAShipOrientation{
  BAShipOrientationHorizontal = 0,
  BAShipOrientationVertical
}BAShipOrientation;

typedef struct {
  uint8_t positionX;
  uint8_t positionY;
  uint8_t fullLength;
  uint8_t remainingLength;
  BAShipOrientation orientation;
}BAShip;

BAShip BAShipMake(uint8_t shipLength);
bool BAShipIsShipDestroyed(BAShip ship);

void drawShip(uint8_t x, uint8_t y, BAShipOrientation orientation, uint8_t shipLength, uint8_t color, Arduboy2 &arduboy);

#endif
