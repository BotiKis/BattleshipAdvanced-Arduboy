#include "BAGame.h"
#include "BACharacter.h"

BAGameCommand BAGame::showCharSelection(){

  BACharacterData availableCharacters[4];
  // make char data
  availableCharacters[0] = characterForID(CharacterIDMatt);
  availableCharacters[1] = characterForID(CharacterIDMimi);
  availableCharacters[2] = characterForID(CharacterIDKenji);
  availableCharacters[3] = characterForID(CharacterIDNaru);

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
      selectedCharIndex = (selectedCharIndex+1)%4;
    }
    if(input->pressed(LEFT_BUTTON)){
      selectedCharIndex = (selectedCharIndex-1)%4;
    }
    if(input->pressed(UP_BUTTON)){
      selectedCharIndex = (selectedCharIndex-2)%4;
    }
    if(input->pressed(DOWN_BUTTON)){
      selectedCharIndex = (selectedCharIndex+2)%4;
    }
    if(input->pressed(A_BUTTON)){
      //playSoundBack();
      return BAGameCommandBack;
    }
    if(input->pressed(B_BUTTON)){
      // clear current player data

      // chars
      delete activePlayer;
      activePlayer = NULL;
      delete opponentPlayer;
      opponentPlayer = NULL;

      this->activePlayer = new BAPlayer(availableCharacters[selectedCharIndex]);

      // get random enemy but not itself
      uint8_t enemyCharIndex;
      do {
        enemyCharIndex = random(4);
      } while(enemyCharIndex == selectedCharIndex);
      
      this->opponentPlayer = new BAPlayer(availableCharacters[enemyCharIndex]);

      return BAGameCommandNext;
    }

    // clear screen
    this->arduboy.clear();


    // draw every character
    for (uint8_t i = 0; i < 4; i++) {
      uint8_t charOriginX = 64 * (i%2);
      uint8_t charOriginY = ((i>1)?32:0);

      // draw char bitmaps
      arduboy.drawBitmap(charOriginX, charOriginY, fillAssetForCharacter(availableCharacters[i].characterID), 32, 32, BLACK);
      arduboy.drawBitmap(charOriginX, charOriginY, outlineAssetForCharacter(availableCharacters[i].characterID), 32, 32, WHITE);

      // Draw name
      drawText(availableCharacters[i].name, charOriginX + 34, charOriginY + 20, (selectedCharIndex == i && selectionAnimator)?BLACK:WHITE, this->arduboy);
    }


    this->arduboy.display();
  }

  return BAGameCommandNone;
}
