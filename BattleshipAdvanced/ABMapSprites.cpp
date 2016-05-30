#include <Arduboy.h>
#include "BAGlobal.h"
#include "ABMapSprites.h"

void drawHorizontalShip(ABPoint origin, byte shipLength, byte color){

  if(shipLength == 1){
    arduboy.drawBitmap(origin.x, origin.y, BAMap_Sprite_Ship_horizontal_single, 8, 8, WHITE);
  }
  else if (shipLength >= 2){
    arduboy.drawBitmap(origin.x, origin.y, BAMap_Sprite_Ship_horizontal_1, 8, 8, WHITE);
    arduboy.drawBitmap(origin.x + ((shipLength-1)*8), origin.y, BAMap_Sprite_Ship_horizontal_3, 8, 8, WHITE);
    
    for(byte i = 1; i < (shipLength-1); i++)
      arduboy.drawBitmap(origin.x + (i*8), origin.y, BAMap_Sprite_Ship_horizontal_2, 8, 8, WHITE);
  }
}

void drawVerticalShip(ABPoint origin, byte shipLength, byte color){
  if(shipLength == 1){
    arduboy.drawBitmap(origin.x, origin.y, BAMap_Sprite_Ship_vertical_single, 8, 8, WHITE);
  }
  else if (shipLength >= 2){
    arduboy.drawBitmap(origin.x, origin.y, BAMap_Sprite_Ship_vertical_1, 8, 8, WHITE);
    arduboy.drawBitmap(origin.x, origin.y + ((shipLength-1)*8), BAMap_Sprite_Ship_vertical_3, 8, 8, WHITE);
    
    for(byte i = 1; i < (shipLength-1); i++)
      arduboy.drawBitmap(origin.x, origin.y+ (i*8), BAMap_Sprite_Ship_vertical_2, 8, 8, WHITE);
  }
}

