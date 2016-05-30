#include "BAMap.h"
#include <Arduboy.h>
#include "BAGlobal.h"
#include "ABMapSprites.h"

void drawMap(BAPlayer *player){

  // flip for watrer animation
  bool waterAnimationStepped = arduboy.everyXFrames(30);
  
    for(byte mapPosY = 0; mapPosY < GAME_BOARD_SIZE_HEIGHT; mapPosY++){
      for(byte mapPosX = 0; mapPosX < GAME_BOARD_SIZE_WIDTH; mapPosX++){

        int currentMapIndex = player->playerBoard[mapPosY][mapPosX];
        
          //=======================================
        // If it's a ship
        if(currentMapIndex >= 0){
           // get actual ship from player
           BAShip currentShip = player->shipAtIndex(currentMapIndex);

           ABPoint shipPosition = currentShip.position;
           shipPosition.x = shipPosition.x*8 + MENU_WIDTH;
           shipPosition.y = shipPosition.y*8;
           
           if(currentShip.horizontal)
            drawHorizontalShip(shipPosition, currentShip.fullLength, WHITE);
           else
            drawVerticalShip(shipPosition, currentShip.fullLength, WHITE);
        }

        //=======================================
        // If it's a Mountain
        else if(currentMapIndex == BAMapTileTypeMountain){
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Mountain, 8, 8, WHITE);
        }

        
        //=======================================
        // If it's a water sprite
        else if(currentMapIndex == BAMapTileTypeWater1){
           arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Water1, 8, 8, WHITE);
           
           if(waterAnimationStepped) // set to next frame
             currentMapIndex = BAMapTileTypeWater2;
        }
        else if(currentMapIndex == BAMapTileTypeWater2){
           arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Water2, 8, 8, WHITE);
           
           if(waterAnimationStepped) // set to next frame
             currentMapIndex = BAMapTileTypeWater3;
        }
        else if(currentMapIndex == BAMapTileTypeWater3){
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Water3, 8, 8, WHITE);
          
           if(waterAnimationStepped) // set to next frame
             currentMapIndex = BAMapTileTypeWater0;
        }

        //=======================================
        // If it's a destroyed ship overdraw the field
        if(currentMapIndex == BAMapTileTypeDestroyedShip){
          arduboy.fillRect(MENU_WIDTH+mapPosX*8, mapPosY*8, 8, 8, BLACK);
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Mountain, 8, 8, WHITE);
        }
        
        //=======================================
        // animate water
        if(currentMapIndex == BAMapTileTypeWater0 && waterAnimationStepped){
          // check probability for new water
          if(random(100) < 1)
            currentMapIndex = BAMapTileTypeWater1;
        }

      }
    }
}
