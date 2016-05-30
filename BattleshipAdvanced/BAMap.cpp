#include "BAMap.h"
#include <Arduboy.h>
#include "BAGlobal.h"
#include "ABMapSprites.h"

void drawMapAtPosition(BAPlayer *player, ABPoint position, bool showShips){

  // flip for watrer animation
  bool waterAnimationStepped = arduboy.everyXFrames(30);
  
    for(byte mapPosY = 0; mapPosY < GAME_BOARD_SIZE_HEIGHT; mapPosY++){
      for(byte mapPosX = 0; mapPosX < GAME_BOARD_SIZE_WIDTH; mapPosX++){

        int currentMapIndex = player->playerBoard[mapPosY][mapPosX];
        
          //=======================================
        // If it's a ship
        if(currentMapIndex >= 0 && showShips){
           // get actual ship from player
           BAShip currentShip = player->shipAtIndex(currentMapIndex);

           ABPoint shipPosition = currentShip.position;
           shipPosition.x = shipPosition.x*8 + MENU_WIDTH + position.x;
           shipPosition.y = shipPosition.y*8 + position.y;
           
           if(currentShip.horizontal)
            drawHorizontalShip(shipPosition, currentShip.fullLength, WHITE);
           else
            drawVerticalShip(shipPosition, currentShip.fullLength, WHITE);
        }

        //=======================================
        // If it's a Mountain
        else if(currentMapIndex == BAMapTileTypeMountain){
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8 + position.x, mapPosY*8 + position.y, BAMap_Sprite_Mountain, 8, 8, WHITE);
        }
        
        //=======================================
        // If it's a water sprite
        else if(currentMapIndex == BAMapTileTypeWater1){
           arduboy.drawBitmap(MENU_WIDTH+mapPosX*8 + position.x, mapPosY*8 + position.y, BAMap_Sprite_Water1, 8, 8, WHITE);
           
           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater2;
        }
        else if(currentMapIndex == BAMapTileTypeWater2){
           arduboy.drawBitmap(MENU_WIDTH+mapPosX*8 + position.x, mapPosY*8 + position.y, BAMap_Sprite_Water2, 8, 8, WHITE);
           
           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater3;
        }
        else if(currentMapIndex == BAMapTileTypeWater3){
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8 + position.x, mapPosY*8 + position.y, BAMap_Sprite_Water3, 8, 8, WHITE);
          
           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater0;
        }
        
        //=======================================
        // animate water
        if(currentMapIndex == BAMapTileTypeWater0 && waterAnimationStepped){
          // check probability for new water
          if(random(100) < 1)
            player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater1;
        }

        //=======================================
        // If it's a destroyed ship overdraw the field
        if(currentMapIndex == BAMapTileTypeDestroyedShip){
          arduboy.fillRect(MENU_WIDTH+mapPosX*8 + position.x, mapPosY*8 + position.y, 8, 8, BLACK);
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8 + position.x, mapPosY*8 + position.y, BAMap_Sprite_Mountain, 8, 8, WHITE);
        }

      }
    }
}


void drawMap(BAPlayer *player, bool showShips){
  drawMapAtPosition(player, ABPointMake(0,0), showShips);
}

