#include "BAShip.h"
#include "BAMapData.h"

BAShip BAShipMake(byte shipLength){
  return  {0, 0, shipLength, shipLength, true};
}

bool BAShipIsShipDestroyed(BAShip ship){
  return ship.remainingLength <= 0;
}

void drawHorizontalShip(uint8_t x, uint8_t y, uint8_t shipLength, uint8_t color, Arduboy &arduboy){

  if(shipLength == 1){
    arduboy.drawBitmap(x, y, BAMap_Sprite_Ship_horizontal_single, 8, 8, color);
  }
  else if (shipLength >= 2){
    arduboy.drawBitmap(x, y, BAMap_Sprite_Ship_horizontal_3, 8, 8, color);
    arduboy.drawBitmap(x + ((shipLength-1)*8), y, BAMap_Sprite_Ship_horizontal_1, 8, 8, color);

    for(byte i = 1; i < (shipLength-1); i++)
      arduboy.drawBitmap(x + (i*8), y, BAMap_Sprite_Ship_horizontal_2, 8, 8, color);
  }
}

void drawVerticalShip(uint8_t x, uint8_t y, uint8_t shipLength, uint8_t color, Arduboy &arduboy){
  if(shipLength == 1){
    arduboy.drawBitmap(x, y, BAMap_Sprite_Ship_vertical_single, 8, 8, color);
  }
  else if (shipLength >= 2){
    arduboy.drawBitmap(x, y, BAMap_Sprite_Ship_vertical_1, 8, 8, color);
    arduboy.drawBitmap(x, y + ((shipLength-1)*8), BAMap_Sprite_Ship_vertical_3, 8, 8, color);

    for(byte i = 1; i < (shipLength-1); i++)
      arduboy.drawBitmap(x, y+ (i*8), BAMap_Sprite_Ship_vertical_2, 8, 8, color);
  }
}
