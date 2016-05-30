#include "BAGame.h"
#include "BAGlobal.h"
#include "BACharacterSelectionHelper.h"
#include "BAVersusScreen.h"
#include "ABMapSprites.h"
#include "BAUI.h"
#include "BAShip.h"


#define MILLIS_SINCE(MILLIS) (millis() - MILLIS)

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
  playerFirstRound = true;
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

    if(showVersusScreenWithPlayerAndEnemy(player->getCharacterData(), enemyPlayer->getCharacterData()) == BAGamesCommandBack){
      continue;
    }

   if(showPositionShips() == BAGamesCommandBack){
      continue;
    }

    showFirstPlayer();
    
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
      playSoundBack();
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

  bool orienteationHorizontal = true;

  while(true){
    if (!arduboy.nextFrame()) continue;
    if (arduboy.everyXFrames(10)) cursorFlip = !cursorFlip;

    // get current ship
    BAShip currentShip = player->shipAtIndex(numberOfPlacedShips);

    // handle input
    globalInput.updateInput();

    if(globalInput.pressed(RIGHT_BUTTON)){
      playerCursor.x++;      
    }
    if(globalInput.pressed(LEFT_BUTTON)){
      playerCursor.x--;
      
      // limit
      playerCursor.x = ((playerCursor.x < 0)? -1 : playerCursor.x); // -1 is okay for menu
    }
    if(globalInput.pressed(UP_BUTTON)){
      playerCursor.y--;
      
      // limit
      playerCursor.y = ((playerCursor.y < 0)? 0 : playerCursor.y);
    }
    if(globalInput.pressed(DOWN_BUTTON)){
      playerCursor.y++;
    }
    if(globalInput.pressed(A_BUTTON)){
      // Flip orientation
      orienteationHorizontal = !orienteationHorizontal;
    }
    
    // move cursor inside bounds if ship gets longer
    int maxX = GAME_BOARD_SIZE_WIDTH - ( orienteationHorizontal ? currentShip.fullLength : 1);
    int maxY = GAME_BOARD_SIZE_HEIGHT - ( !orienteationHorizontal ? currentShip.fullLength : 1); 
    playerCursor.y = ((playerCursor.y > maxY)? maxY : playerCursor.y);
    playerCursor.x = ((playerCursor.x > maxX)? maxX : playerCursor.x);

    
    if(globalInput.pressed(B_BUTTON)){

      // Check if cancel was pressed
      if(playerCursor.x < 0){
        playSoundBack();
        return BAGamesCommandBack;
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

          if (player->playerBoard[playerCursor.y+dY][playerCursor.x+dX] >= 0 || player->playerBoard[playerCursor.y+dY][playerCursor.x+dX] == BAMapTileTypeMountain) {
            safe = false;
            break;
          }
        }
        
        if (!safe) {
          // play error sound and ignore
          playSoundErr();
        }
        else{
          // nope, place ship!
          playSoundSuccess();
          
          // update  orientation
          currentShip.horizontal = orienteationHorizontal;
          player->updateShipAtIndex(numberOfPlacedShips, currentShip);

          // store on map
          for (int len = 0; len < currentShip.fullLength; len++) {
            int dX = 0, dY = 0;
  
            if (orienteationHorizontal)
              dX = len;
            else
              dY = len;
  
            player->playerBoard[playerCursor.y+dY][playerCursor.x+dX] =  numberOfPlacedShips; // write index of ship on the map
          }
          
          numberOfPlacedShips++;

          // check if done
          if(numberOfPlacedShips == player->numberOfShips){
            return BAGamesCommandNext;
          }
        }
        
      }
    }
    
    // clear screen
    arduboy.clear();

    // Draw map for player
    drawMap(player);
        
    //=======================================
    // draw menu
    arduboy.setCursor(1,1);
    arduboy.println(player->getCharacterData().name);
    arduboy.println(player->numberOfShips);

    // Info fields
    arduboy.drawBitmap(0, 28, BAUI_a_rotate, 30, 8, WHITE);
    arduboy.drawBitmap(0, 40, BAUI_b_place, 30, 8, WHITE);

    //=======================================
    // Draw cursor
    // only draw cursor if index is inside map
    if(playerCursor.x >= 0){

      ABPoint shipPos;
      shipPos.x = MENU_WIDTH + playerCursor.x*8;
      shipPos.y = playerCursor.y*8;
      
      // draw current ship
      if(orienteationHorizontal){
        drawHorizontalShip(shipPos, currentShip.fullLength, WHITE);
      }
      else{
        drawVerticalShip(shipPos, currentShip.fullLength, WHITE);
      }
      
      
      ABRect cursorFrame;
      cursorFrame.origin.x = shipPos.x + (cursorFlip ? 1:0);
      cursorFrame.origin.y = shipPos.y + (cursorFlip ? 1:0);
      cursorFrame.size.width = cursorFlip ? 6 : 8;
      cursorFrame.size.height = cursorFlip ? 6 : 8;
      arduboy.drawRect(cursorFrame.origin.x, cursorFrame.origin.y, cursorFrame.size.width, cursorFrame.size.height, WHITE);

      // Draw cancle button
      arduboy.drawBitmap(0, 55, BAUI_cancel, 30, 8, WHITE);
    }
    else{
      // Draw cancel button
      arduboy.drawBitmap(0, 55, BAUI_cancel_selected, 30, 8, WHITE);
    }
    
    arduboy.display();
  }

  return BAGamesCommandErr;
}

void BAGame::showFirstPlayer(){

  bool animationDone = false;
  bool animationFlip = false;

  // 0 = player, 1 = AI
  byte firstPlayer = random(2);

  unsigned long startTime = millis();
  
  // screenloop
  while(true){
    if (!arduboy.nextFrame()) continue;
    if(arduboy.everyXFrames(6)) animationFlip = !animationFlip;

    // handle input
    globalInput.updateInput();

    // calc time
    unsigned long deltaTime = MILLIS_SINCE(startTime);

    if(globalInput.pressed(A_BUTTON) || globalInput.pressed(B_BUTTON)){
      // close screen
      if(animationDone && deltaTime > 1000){
        return;
      }
      else{
        animationDone = true;
      }
    }

    // check if animation should stop
    animationDone = deltaTime > 4000 || animationDone;
    
    // clear screen
    arduboy.clear();

    // write stuff
    arduboy.setCursor(22, 14);
    arduboy.print("BATTLE BEGINS!");
    arduboy.setCursor(25, 26);
    arduboy.print("First player:");
    arduboy.setCursor(49, 38);

    if(animationDone){
      arduboy.print( (playerFirstRound ? player->getCharacterData().name: enemyPlayer->getCharacterData().name));
      arduboy.setCursor(13, 48);
      if(animationFlip) arduboy.print("press a button...");
    }
     else
      arduboy.print( (animationFlip ? player->getCharacterData().name: enemyPlayer->getCharacterData().name));

    // show
    arduboy.display();
  }
}


