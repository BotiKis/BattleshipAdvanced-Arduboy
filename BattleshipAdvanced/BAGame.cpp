#include "BAGame.h"
#include "BAGlobal.h"
#include "BACharacterSelectionHelper.h"
#include "BAVersusScreen.h"
#include "ABMapSprites.h"


// --------------------------------------------------
// Helper
// --------------------------------------------------
void drawSelection(ABPoint offset, byte animator);
void drawTriangles(ABPoint offset, byte animator);

// --------------------------------------------------
// GAME CLASS
// --------------------------------------------------
BAGame::BAGame(){
  player = NULL;
  enemyPlayer = NULL;
}

bool BAGame::start(){

  
  // Main game Loop
  while(true){
    
    // reset game
    reset();
    
    // Show character selection
    if(showCharSelect() == BAGamesCommandBack){
      playSoundBack();
      return true; // return to menu if user wants
    }

    if(showVersusScreenWithPlayerAndEnemy(player->getCharacterData(), enemyPlayer->getCharacterData())){
      playSoundBack();
      continue;
    }
    playSoundSuccess();

   if(showPositionShips()){
      playSoundBack();
      continue;
    }
    
  }

  return true;
}


void BAGame::reset(){
  delete player;
  delete enemyPlayer;
  
  player = NULL;
  enemyPlayer = NULL;
}

// --------------------------------------------------
// CHAR SELECTION
// --------------------------------------------------

BAGamesCommand BAGame::showCharSelect(){

  BACharacterData availableCharacters[4];
  // make char data
  // name, spriteID, #OfShots per round, small ships, medium ships, large ships, difficulty
  availableCharacters[0] = BACharacterDataMake("Matt", CharacterIDMatt, 1, 3, 2, 1, CharDifficultyEasy);
  availableCharacters[1] = BACharacterDataMake("Mimi", CharacterIDMimi, 1, 5, 2, 1, CharDifficultyHard);
  availableCharacters[2] = BACharacterDataMake("Kenji", CharacterIDKenji, 1, 2, 2, 2, CharDifficultyHard);
  availableCharacters[3] = BACharacterDataMake("Naru", CharacterIDNaru, 2, 2, 2, 0, CharDifficultyHard);


// helper
  byte selectedCharIndex = 0;
  byte bgAnimator = 0;
  byte selectionAnimator = 0;

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
    if(globalInput.pressed(B_BUTTON)){
      player = new BAPlayer(availableCharacters[selectedCharIndex]);
      
      // get random enemy but not itself
      byte enemyCharIndex = random(4);
      while(enemyCharIndex == selectedCharIndex) enemyCharIndex = random(4);
      enemyPlayer = new BAPlayer(availableCharacters[enemyCharIndex]);
      
      return BAGamesCommandNext;
    }


    if (arduboy.everyXFrames(3)){
      bgAnimator++;
      bgAnimator = bgAnimator%3;
    }
    if (arduboy.everyXFrames(15)){
      selectionAnimator++;
      selectionAnimator = selectionAnimator%2;
    }
    
    ABPoint offset;
    offset.x = ( ((selectedCharIndex%2) == 0)?0:64);
    offset.y = ( (selectedCharIndex > 1)?32:0);
    
    // clear screen
    arduboy.clear();

    // draw stuff
    drawSelection(offset, selectionAnimator);
    drawTriangles(offset, bgAnimator);

    // draw chars
    for(size_t i = 0; i < 4; i++){
      ABPoint charOffset;
      charOffset.x = 64 * (i%2);
      charOffset.y = ((i>1)?32:0);
      drawCharacterSelectionAsset(availableCharacters[i], charOffset);
    }
    
    arduboy.display();
  }

  return BAGamesCommandErr;
}


// --------------------------------------------------
// POSITION SHIPS
// --------------------------------------------------

BAGamesCommand BAGame::showPositionShips(){

  // store information
  ABPoint playerCursor = ABPointMake(6, 4);
  bool cursorFlip = true;
  byte numberOfPlacedShips = 0;

  while(true){
     if (!arduboy.nextFrame()) continue;
     if (arduboy.everyXFrames(10)) cursorFlip = !cursorFlip;

    // handle input
    globalInput.updateInput();

    if(globalInput.pressed(RIGHT_BUTTON)){
      playerCursor.x++;

      // limit
      playerCursor.x = ((playerCursor.x >= GAME_BOARD_SIZE_WIDTH)? (GAME_BOARD_SIZE_WIDTH-1) : playerCursor.x);
    }
    if(globalInput.pressed(LEFT_BUTTON)){
      playerCursor.x--;
      
      // limit
      playerCursor.x = ((playerCursor.x < 0)? 0 : playerCursor.x);
    }
    if(globalInput.pressed(UP_BUTTON)){
      playerCursor.y--;
      
      // limit
      playerCursor.y = ((playerCursor.y < 0)? 0 : playerCursor.y);
    }
    if(globalInput.pressed(DOWN_BUTTON)){
      playerCursor.y++;

      // limit
      playerCursor.y = ((playerCursor.y >= GAME_BOARD_SIZE_HEIGHT)? (GAME_BOARD_SIZE_HEIGHT-1) : playerCursor.y);
    }
    if(globalInput.pressed(A_BUTTON)){
      // Back
      return BAGamesCommandBack;
    }
    if(globalInput.pressed(B_BUTTON)){
      // place ship
      playSoundSuccess();
    }
    
    // clear screen
    arduboy.clear();

    // Draw map for player
     drawMap(player);

    // Draw map
    for(byte mapPosY = 0; mapPosY < GAME_BOARD_SIZE_HEIGHT; mapPosY++){
      for(byte mapPosX = 0; mapPosX < GAME_BOARD_SIZE_WIDTH; mapPosX++){
        
        //=======================================
        // Draw cursor
        ABRect cursorFrame;
        cursorFrame.origin.x = MENU_WIDTH + playerCursor.x*8 + (cursorFlip ? 1:0);
        cursorFrame.origin.y = playerCursor.y*8 + (cursorFlip ? 1:0);
        cursorFrame.size.width = cursorFlip ? 6 : 8;
        cursorFrame.size.height = cursorFlip ? 6 : 8;
        arduboy.drawRect(cursorFrame.origin.x, cursorFrame.origin.y, cursorFrame.size.width, cursorFrame.size.height, WHITE);
      }
    }
    
    arduboy.display();
  }

  return BAGamesCommandErr;
}


