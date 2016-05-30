#include "BAMap.h"
#include <Arduboy.h>
#include "BAGlobal.h"
#include "ABMapSprites.h"

void drawMap(BAPlayer *player){

  // flip for watrer animation
  bool waterAnimationStepped = arduboy.everyXFrames(30);
  
    for(byte mapPosY = 0; mapPosY < GAME_BOARD_SIZE_HEIGHT; mapPosY++){
      for(byte mapPosX = 0; mapPosX < GAME_BOARD_SIZE_WIDTH; mapPosX++){
          //=======================================
        // If it's a ship
        if(player->playerBoard[mapPosY][mapPosX] >= 0){
          // TODO ORIENTATION AND TYPE
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Ship_horizontal_single, 8, 8, WHITE);
        }


        //=======================================
        // If it's a Mountain
        else if(player->playerBoard[mapPosY][mapPosX] == BAMapTileTypeMountain){
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Mountain, 8, 8, WHITE);
        }

        
        //=======================================
        // If it's a water sprite
        else if(player->playerBoard[mapPosY][mapPosX] == BAMapTileTypeWater1){
           arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Water1, 8, 8, WHITE);
           
           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater2;
        }
        else if(player->playerBoard[mapPosY][mapPosX] == BAMapTileTypeWater2){
           arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Water2, 8, 8, WHITE);
           
           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater3;
        }
        else if(player->playerBoard[mapPosY][mapPosX] == BAMapTileTypeWater3){
          arduboy.drawBitmap(MENU_WIDTH+mapPosX*8, mapPosY*8, BAMap_Sprite_Water3, 8, 8, WHITE);
          
           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater0;
        }

        
        //=======================================
        // animate water
        if(player->playerBoard[mapPosY][mapPosX] == BAMapTileTypeWater0 && waterAnimationStepped){
          // check probability for new water
          if(random(100) < 1)
            player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater1;
        }

      }
    }
}
