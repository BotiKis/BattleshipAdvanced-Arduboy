#include "BAShip.h"
#include "BAMapData.h"

BAShip BAShipMake(uint8_t shipLength){
  return  {0, 0, shipLength, shipLength, BAShipOrientationHorizontal};
}

bool BAShipIsShipDestroyed(BAShip ship){
  return ship.remainingLength <= 0;
}

void drawShip(uint8_t x, uint8_t y, BAShipOrientation orientation, uint8_t shipLength, uint8_t color, Arduboy &arduboy){
bool horizontal = (orientation == BAShipOrientationHorizontal);

  if(shipLength == 1){
    arduboy.drawBitmap(x, y, horizontal?BAMap_Sprite_Ship_horizontal_single:BAMap_Sprite_Ship_vertical_single, 8, 8, color);
  }
  else if (shipLength >= 2){
    int8_t lastPartPos = ((shipLength-1)*8);
    arduboy.drawBitmap(x,  y, horizontal?BAMap_Sprite_Ship_horizontal_1:BAMap_Sprite_Ship_vertical_1, 8, 8, color);
    arduboy.drawBitmap(x + horizontal?lastPartPos:0, y + horizontal?0:lastPartPos, horizontal?BAMap_Sprite_Ship_horizontal_3:BAMap_Sprite_Ship_vertical_3, 8, 8, color);

    for(int8_t i = 1; i < (shipLength-1); i++){
      int8_t middlePartPos = (i*8);
      arduboy.drawBitmap(x + horizontal?middlePartPos:0, y + horizontal?0:middlePartPos, horizontal?BAMap_Sprite_Ship_horizontal_2:BAMap_Sprite_Ship_vertical_2, 8, 8, color);
    }
  }
}
