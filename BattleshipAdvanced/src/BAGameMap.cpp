#include "BAGame.h"
#include "BAMapData.h"
#include "BAShip.h"

void BAGame::drawMapAtPosition(BAPlayer *player, uint8_t x, uint8_t y, bool showShips){

  // flip for watrer animation
  bool waterAnimationStepped = this->arduboy.everyXFrames(30);

    for(int mapPosY = 0; mapPosY < BAPlayer::gameBoardSize().height; mapPosY++){
      for(int mapPosX = 0; mapPosX < BAPlayer::gameBoardSize().width; mapPosX++){

        int currentMapIndex = player->playerBoard[mapPosY][mapPosX];

          //=======================================
        // If it's a ship
        if(currentMapIndex >= 0 && showShips){
           // get actual ship from player
           BAShip currentShip = player->shipAtIndex(currentMapIndex);

           uint8_t shipPosX = currentShip.positionX*8  + x;
           uint8_t shipPosY = currentShip.positionY*8 + y;

           drawShip(shipPosX, shipPosY, currentShip.orientation, currentShip.fullLength, WHITE, this->arduboy);
        }

        //=======================================
        // If it's a Mountain
        if(currentMapIndex == BAMapTileTypeMountain){
          this->arduboy.drawBitmap(mapPosX*8 + x, mapPosY*8 + y, BAMap_Sprite_Mountain, 8, 8, WHITE);
        }

        //=======================================
        // If it's a water sprite
        if(currentMapIndex == BAMapTileTypeWater1){
           this->arduboy.drawBitmap(mapPosX*8 + x, mapPosY*8 + y, BAMap_Sprite_Water1, 8, 8, WHITE);

           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater2;
        }
        else if(currentMapIndex == BAMapTileTypeWater2){
           this->arduboy.drawBitmap(mapPosX*8 + x, mapPosY*8 + y, BAMap_Sprite_Water2, 8, 8, WHITE);

           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater3;
        }
        else if(currentMapIndex == BAMapTileTypeWater3){
          this->arduboy.drawBitmap(mapPosX*8 + x, mapPosY*8 + y, BAMap_Sprite_Water3, 8, 8, WHITE);

           if(waterAnimationStepped) // set to next frame
             player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater0;
        }

        //=======================================
        // animate water
        if(currentMapIndex == BAMapTileTypeWater0 && waterAnimationStepped){
          // check probability for new water
          if(random(100) < 10)
            player->playerBoard[mapPosY][mapPosX] = BAMapTileTypeWater1;
        }

        //=======================================
        // If it's a destroyed ship overdraw the field
        if(currentMapIndex == BAMapTileTypeDestroyedShip){
          this->arduboy.drawBitmap(mapPosX*8 + x, mapPosY*8 + y, BAMap_Sprite_Mountain, 8, 8, WHITE);
        }

      }
    }
}


void BAGame::drawMap(BAPlayer *player, bool showShips){
  drawMapAtPosition(player, 0, 0, showShips);
}
