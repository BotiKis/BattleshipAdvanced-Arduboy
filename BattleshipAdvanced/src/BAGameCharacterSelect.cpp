#include "BAGame.h"
#include "BACharacter.h"
#include "BAMapData.h"
#include "BAShip.h"

BAGameCommand BAGame::showCharSelection(){

  // make char names
  // Dont use char data class here to keep memory low, name is totaly suffecient
  // Array needs to be in same order as ENUM CharacterID to match with the
  // selectedCharIndex to be able to draw the correct char on screen.
  const char *availableCharacters[] = {"Matt", "Mimi", "Kenji", "Naru"};

  // UI Stuff
  uint8_t selectedCharIndex = 0;
  uint8_t selectionAnimator = 0;

  while(true){

    // Wait for next frame
    if (!this->arduboy.nextFrame()) continue;

    // for selection animation
    if (arduboy.everyXFrames(15)){
      selectionAnimator++;
      selectionAnimator = selectionAnimator%2;
    }

    // --------------------------------
    // udpate input
    this->input->updateInput();

    // check input
    if(input->pressed(RIGHT_BUTTON)){
      selectedCharIndex = (uint8_t)(selectedCharIndex+1)%4;
      selectionAnimator = 0;
    }
    if(input->pressed(LEFT_BUTTON)){
      selectedCharIndex = (uint8_t)(selectedCharIndex-1)%4;
      selectionAnimator = 0;
    }
    if(input->pressed(UP_BUTTON)){
      selectedCharIndex = (uint8_t)(selectedCharIndex-2)%4;
      selectionAnimator = 0;
    }
    if(input->pressed(DOWN_BUTTON)){
      selectedCharIndex = (uint8_t)(selectedCharIndex+2)%4;
      selectionAnimator = 0;
    }
    if(input->pressed(A_BUTTON)){
      //playSoundBack();
      return BAGameCommandBack;
    }
    if(input->pressed(B_BUTTON)){
      // clear current player data

      // chars
      delete this->activePlayer;
      this->activePlayer = NULL;
      delete this->opponentPlayer;
      this->opponentPlayer = NULL;

      this->activePlayer = new BAPlayer((CharacterID)selectedCharIndex);

      // get random enemy but not itself
      uint8_t enemyCharIndex;
      do {
        enemyCharIndex = random(4);
      } while(enemyCharIndex == selectedCharIndex);

      this->opponentPlayer = new BAPlayer((CharacterID)enemyCharIndex);

      // place enemy ships
      for(int8_t i = 0; i < this->opponentPlayer->numberOfAllShips(); i++){
        BAShip currentShip = this->opponentPlayer->shipAtIndex(i);

        // randomize ship and collision detect
        bool collides = true;
        do {
          currentShip.positionX = random(0, BAPlayer::gameBoardSize().width);
          currentShip.positionY = random(0, BAPlayer::gameBoardSize().height);
          currentShip.orientation = ((random()%2) == 0)?BAShipOrientationHorizontal:BAShipOrientationVertical;
          collides = this->opponentPlayer->shipCollidesOnMap(currentShip);
        } while(collides);

        // update ship
        this->opponentPlayer->updateShipAtIndex(i, currentShip);

        // store on map
        for (int8_t len = 0; len < currentShip.fullLength; len++) {
          int8_t dX = 0, dY = 0;

          if (currentShip.orientation == BAShipOrientationHorizontal)
            dX = len;
          else
            dY = len;

          this->opponentPlayer->playerBoard[currentShip.positionY+dY][currentShip.positionX+dX] =  i; // write index of ship on the map
        }
      }


      return BAGameCommandNext;
    }

    // clear screen
    this->arduboy.clear();


    // draw every character
    for (uint8_t i = 0; i < 4; i++) {
      uint8_t charOriginX = 64 * (i%2);
      uint8_t charOriginY = ((i>1)?32:0);

      // draw char bitmaps
      //
      arduboy.drawBitmap(charOriginX, charOriginY, BACharacterData::fillAssetForCharacter((CharacterID)i), 32, 32, BLACK);
      arduboy.drawBitmap(charOriginX, charOriginY, BACharacterData::outlineAssetForCharacter((CharacterID)i), 32, 32, WHITE);

      // Draw name
      drawText(availableCharacters[i], charOriginX + 34, charOriginY + 20, (selectedCharIndex == i && selectionAnimator)?BLACK:WHITE, this->arduboy);
    }


    this->arduboy.display();
  }

  return BAGameCommandNone;
}
