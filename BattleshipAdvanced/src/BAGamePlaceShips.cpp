#include "BAGame.h"
#include "BAMapData.h"

#define GAME_BOARD_SIZE_WIDTH 12
#define GAME_BOARD_SIZE_HEIGHT 8

BAGameCommand BAGame::showPlaceShips(){

  // for animating stuff
  bool animationFlip = true;
  uint16_t startTime = millis();

  // ===========================
  // info panel loop
  while(true){
    if (!this->arduboy.nextFrame()) continue;
    if (this->arduboy.everyXFrames(10)) animationFlip = !animationFlip;

    // handle input
    this->input->updateInput();

    if(this->input->pressed(B_BUTTON) || this->input->pressed(A_BUTTON)){
      break;
    }

    // clear screen
    this->arduboy.clear();

    drawText("PLACE YOUR SHIPS!", 14, 2, WHITE, this->arduboy);
    char numberOfShipsBuffer [3];

    drawText("Small:", 8, 20, WHITE, this->arduboy);
    sprintf (numberOfShipsBuffer, "%dx", this->activePlayer->getCharacterData()->numberOfSmallShips);
    drawTextRightAligned(numberOfShipsBuffer, 84, 20, WHITE, this->arduboy);

    drawText("Medium:", 8, 32, WHITE, this->arduboy);
    sprintf (numberOfShipsBuffer, "%dx", this->activePlayer->getCharacterData()->numberOfMediumShips);
    drawTextRightAligned(numberOfShipsBuffer, 84, 32, WHITE, this->arduboy);

    drawText("Big:", 8, 44, WHITE, this->arduboy);
    sprintf (numberOfShipsBuffer, "%dx", this->activePlayer->getCharacterData()->numberOfLargeShips);
    drawTextRightAligned(numberOfShipsBuffer, 84, 44, WHITE, this->arduboy);

    // draw ships
    drawHorizontalShip(96, 20, 1, WHITE, this->arduboy);
    drawHorizontalShip(96, 32, 2, WHITE, this->arduboy);
    drawHorizontalShip(96, 44, 3, WHITE, this->arduboy);

    // draw press button
    if ( (MILLIS_SINCE(startTime) > 1000) && animationFlip) {
      drawText("Press A or B", 28, 56, WHITE, this->arduboy);
    }

    this->arduboy.display();
  }



  // ======================================================
  // ======================================================
  // place ships loop
  // ======================================================
  // ======================================================


  // store information
  ABPoint playerCursor = ABPointMake(6, 4);
  bool cursorFlip = true;
  byte numberOfPlacedShips = 0;
  bool orienteationHorizontal = true;

  // set refire rate
  this->input->refireAfterMillis = 150;

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
        // set refire rate
        this->input->refireAfterMillis = BA_INPUT_REFIRERATE_DEFAULT;

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
          if(numberOfPlacedShips == this->activePlayer->numberOfAllShips()){
            // set refire rate
            this->input->refireAfterMillis = BA_INPUT_REFIRERATE_DEFAULT;

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

    this->arduboy.drawBitmap(0, 8, BAUI_remaining_ships, 30, 8, WHITE);

    char remainingShipsBuffer[3] = {0};
    drawText(this->activePlayer->getCharacterData()->name, 0, 0, WHITE, this->arduboy);
    sprintf (remainingShipsBuffer, "%d", this->activePlayer->numberOfAllShips() - numberOfPlacedShips);
    drawText(remainingShipsBuffer, 0, 16, WHITE, this->arduboy);

    // Info fields
    this->arduboy.drawBitmap(0, 28, BAUI_a_rotate, 30, 8, WHITE);
    this->arduboy.drawBitmap(0, 40, BAUI_b_place, 30, 8, WHITE);

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

      // Do selection with sprites
      this->arduboy.drawBitmap(shipPosX, shipPosY, cursorFlip?BAMap_Cursor_01:BAMap_Cursor_02, 8, 8, WHITE);

      // Draw cancle button
      this->arduboy.drawBitmap(0, 54, BAUI_cancel, 30, 8, WHITE);
    }
    else{
      // Draw cancel button
      this->arduboy.drawBitmap(0, 54, BAUI_cancel_selected, 30, 8, WHITE);
    }

    this->arduboy.display();
  }

  return BAGameCommandError;
}
