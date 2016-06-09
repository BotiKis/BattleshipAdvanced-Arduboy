#include "BAGame.h"

BAGameCommand BAGame::showCharSelection(){

  BACharacterData availableCharacters[4];
  // make char data
  // name, spriteID, #OfShots per round, small ships, medium ships, large ships, difficulty
  availableCharacters[0] = BACharacterDataMake("Matt", CharacterIDMatt, 1, 3, 2, 1, CharDifficultyEasy);
  availableCharacters[1] = BACharacterDataMake("Mimi", CharacterIDMimi, 1, 5, 2, 1, CharDifficultyHard);
  availableCharacters[2] = BACharacterDataMake("Kenji", CharacterIDKenji, 1, 2, 2, 2, CharDifficultyHard);
  availableCharacters[3] = BACharacterDataMake("Naru", CharacterIDNaru, 2, 2, 2, 0, CharDifficultyHard);

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
    this->input->updateInput(arduboy);

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
      this->activePlayer = new BAPlayer(availableCharacters[selectedCharIndex]);

      // get random enemy but not itself
      byte enemyCharIndex = random(4);
      while(enemyCharIndex == selectedCharIndex) enemyCharIndex = random(4);
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
