#include "BAGame.h"

#define GAME_BOARD_SIZE_WIDTH 12
#define GAME_BOARD_SIZE_HEIGHT 8

BAGameCommand BAGame::showPlaceShips(){

  // store information
  ABPoint playerCursor = ABPointMake(6, 4);
  bool cursorFlip = true;
  byte numberOfPlacedShips = 0;
  bool orienteationHorizontal = true;

  // ===========================
  // info panel loop
  while(true){

    if (!this->arduboy.nextFrame()) continue;

    // handle input
    this->input->updateInput();

    if(this->input->pressed(B_BUTTON) || this->input->pressed(A_BUTTON)){
      break;
    }

    // clear screen
    this->arduboy.clear();

    drawText("Place your ships!", 26, 18, WHITE, this->arduboy);
    char numberOfShipsBuffer [3];

    sprintf (numberOfShipsBuffer, "%d", this->activePlayer->getCharacterData().numberOfSmallShips);
    drawText(numberOfShipsBuffer, 8, 28, WHITE, this->arduboy);

    sprintf (numberOfShipsBuffer, "%d", this->activePlayer->getCharacterData().numberOfMediumShips);
    drawText(numberOfShipsBuffer, 8, 30, WHITE, this->arduboy);

    sprintf (numberOfShipsBuffer, "%d", this->activePlayer->getCharacterData().numberOfLargeShips);
    drawText(numberOfShipsBuffer, 8, 42, WHITE, this->arduboy);

    // draw ships
    drawHorizontalShip(96, 28, 1, WHITE, this->arduboy);
    drawHorizontalShip(96, 30, 1, WHITE, this->arduboy);
    drawHorizontalShip(96, 42, 1, WHITE, this->arduboy);

    this->arduboy.display();
  }

  // ===========================
  // place ships loop
  while(true){
    if (!this->arduboy.nextFrame()) continue;
    if (this->arduboy.everyXFrames(10)) cursorFlip = !cursorFlip;

    // get current ship
    BAShip currentShip = this->activePlayer->shipAtIndex(numberOfPlacedShips);

    // handle input
    this->input->updateInput();

    if(this->input->pressed(RIGHT_BUTTON)){
      playerCursor.x++;
    }
    if(this->input->pressed(LEFT_BUTTON)){
      playerCursor.x--;

      // limit
      playerCursor.x = ((playerCursor.x < 0)? -1 : playerCursor.x); // -1 is okay for menu
    }
    if(this->input->pressed(UP_BUTTON)){
      playerCursor.y--;

      // limit
      playerCursor.y = ((playerCursor.y < 0)? 0 : playerCursor.y);
    }
    if(this->input->pressed(DOWN_BUTTON)){
      playerCursor.y++;
    }
    if(this->input->pressed(A_BUTTON)){
      // Flip orientation
      orienteationHorizontal = !orienteationHorizontal;
    }

    // move cursor inside bounds if ship gets longer
    int maxX = GAME_BOARD_SIZE_WIDTH - ( orienteationHorizontal ? currentShip.fullLength : 1);
    int maxY = GAME_BOARD_SIZE_HEIGHT - ( !orienteationHorizontal ? currentShip.fullLength : 1);
    playerCursor.y = ((playerCursor.y > maxY)? maxY : playerCursor.y);
    playerCursor.x = ((playerCursor.x > maxX)? maxX : playerCursor.x);


    if(this->input->pressed(B_BUTTON)){

      // Check if cancel was pressed
      if(playerCursor.x < 0){
        //playSoundBack();
        return BAGameCommandBack;
      }
      else{

        // check if ship collides with other ship or mountain
        bool safe = true;
        for (int len = 0; len < currentShip.fullLength; len++) {
          int dX = 0, dY = 0;

          if (orienteationHorizontal)
            dX = len;
          else
            dY = len;

          if (this->activePlayer->playerBoard[playerCursor.y+dY][playerCursor.x+dX] >= 0 || this->activePlayer->playerBoard[playerCursor.y+dY][playerCursor.x+dX] == BAMapTileTypeMountain) {
            safe = false;
            break;
          }
        }

        if (!safe) {
          // play error sound and ignore
          //playSoundErr();
        }
        else{
          // Yesss, place ship!
          //playSoundSuccess();

          // update  orientation
          currentShip.horizontal = orienteationHorizontal;
          currentShip.positionX = playerCursor.x;
          currentShip.positionY = playerCursor.y;
          this->activePlayer->updateShipAtIndex(numberOfPlacedShips, currentShip);

          // store on map
          for (int8_t len = 0; len < currentShip.fullLength; len++) {
            int8_t dX = 0, dY = 0;

            if (orienteationHorizontal)
              dX = len;
            else
              dY = len;

            this->activePlayer->playerBoard[playerCursor.y+dY][playerCursor.x+dX] =  numberOfPlacedShips; // write index of ship on the map
          }

          numberOfPlacedShips++;

          // check if done
          if(numberOfPlacedShips == this->activePlayer->numberOfShips){
            return BAGameCommandNext;
          }
        }

      }
    }

    // clear screen
    this->arduboy.clear();

    // Draw map for player
    this->drawMapAtPosition(this->activePlayer, 32, 0, true);

    //=======================================
    // draw menu
    char remainingShipsBuffer[3] = {0};
    drawText(this->activePlayer->getCharacterData().name, 0, 0, WHITE, this->arduboy);
    sprintf (remainingShipsBuffer, "%d", this->activePlayer->numberOfShips - numberOfPlacedShips);
    drawText(remainingShipsBuffer, 0, 8, WHITE, this->arduboy);


    // Info fields
    this->arduboy.drawBitmap(0, 28, BAUI_a_rotate, 30, 9, WHITE);
    this->arduboy.drawBitmap(0, 40, BAUI_b_place, 30, 9, WHITE);

    //=======================================
    // Draw cursor
    // only draw cursor if index is inside map
    if(playerCursor.x >= 0){

      ABPoint shipPos;
      uint8_t shipPosX = 32 + playerCursor.x*8;
      uint8_t shipPosY = playerCursor.y*8;

      // draw current ship
      if(orienteationHorizontal){
        drawHorizontalShip(shipPosX, shipPosY, currentShip.fullLength, WHITE, this->arduboy);
      }
      else{
        drawVerticalShip(shipPosX, shipPosY, currentShip.fullLength, WHITE, this->arduboy);
      }

      uint8_t cursorsOriginX = shipPosX + (cursorFlip ? 1:0);
      uint8_t cursorsOriginY = shipPosY + (cursorFlip ? 1:0);
      uint8_t cursorsSize = cursorFlip ? 6 : 8;
      this->arduboy.drawRect(cursorsOriginX, cursorsOriginY, cursorsSize, cursorsSize, WHITE);

      // Draw cancle button
      this->arduboy.drawBitmap(0, 54, BAUI_cancel, 30, 9, WHITE);
    }
    else{
      // Draw cancel button
      this->arduboy.drawBitmap(0, 54, BAUI_cancel_selected, 30, 9, WHITE);
    }

    this->arduboy.display();
  }

  return BAGameCommandError;
}
