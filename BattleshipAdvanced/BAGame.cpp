#include "BAGame.h"
#include "BAGlobal.h"

BAGame::BAGame(){
}

bool BAGame::start(){
  // Main game Loop
  
  while(true){
    // back to menu
    if(showCharSelect() == BAGamesCommandBack) return true;
  }

  return true;
}


// --------------------------------------------------
// CHAR SELECTION
// --------------------------------------------------

BAGamesCommand BAGame::showCharSelect(){

  BACharacterData availableCharacters[4];
  // make char data
  // name, spriteID, #OfShots per round, small ships, medium ships, large ships, difficulty
  availableCharacters[0] = BACharacterDataMake("Tom", 1, 1, 3, 2, 1, CharDifficultyEasy);
  availableCharacters[1] = BACharacterDataMake("Eva", 2, 1, 5, 2, 1, CharDifficultyHard);
  availableCharacters[2] = BACharacterDataMake("Matt", 3, 1, 2, 2, 2, CharDifficultyHard);
  availableCharacters[3] = BACharacterDataMake("Joanne", 4, 2, 2, 2, 0, CharDifficultyHard);


// helper
  byte selectedCharIndex = 0;
  bool selectionFlip = true;

// Screenloop
  while(true){
    if (!arduboy.nextFrame()) continue;

    // update input
    globalInput.updateInput();

    // check input
    if(globalInput.pressed(RIGHT_BUTTON)){
      selectedCharIndex = (selectedCharIndex+1)%4;
    }
    if(globalInput.pressed(LEFT_BUTTON)){
      selectedCharIndex = (selectedCharIndex-1)%4;
    }
    if(globalInput.pressed(UP_BUTTON)){
      selectedCharIndex = (selectedCharIndex-2)%4;
    }
    if(globalInput.pressed(DOWN_BUTTON)){
      selectedCharIndex = (selectedCharIndex+2)%4;
    }
    if(globalInput.pressed(A_BUTTON)){
      return BAGamesCommandBack;
    }

    // clear screen
    arduboy.clear();

    // draw selection
    
    if (arduboy.everyXFrames(15)) selectionFlip = !selectionFlip;
    const int padding = 1;
    ABRect frame;
    frame.origin.x = ((selectedCharIndex % 2) * 64) + ((selectionFlip) ? padding : 0);
    frame.origin.y = ((selectedCharIndex > 1)?32:0) + ((selectionFlip) ? padding : 0);
    frame.size.width = 64 - ((selectionFlip) ? (padding*2) : 0);
    frame.size.height = 32 - ((selectionFlip) ? (padding*2) : 0);

    arduboy.drawRect(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height, WHITE);

    arduboy.display();
  }

  return BAGamesCommandErr;
}
