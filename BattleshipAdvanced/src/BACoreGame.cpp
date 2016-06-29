#include "BAGame.h"
#include "BAMapData.h"

// =============================================
// Main game method

BAGameCommand BAGame::playGame(){

  bool gameOver = false;

  while (!gameOver) {

    // Switch between player and AI
    if(this->playerFirstRound){

      // Animate between maps
      this->animateFromPlayerToPlayer(this->opponentPlayer, this->activePlayer, false);

      // Do a turn while player has shots
      for (uint8_t i = 0; i < this->activePlayer->getCharacterData()->numberOfShots; i++) {
        this->runPlayerTurn();

        // check if player has won
        gameOver = this->opponentPlayer->numberOfRemainingShips() <= 0;

        // break if player has won
        if (gameOver) break;
      }
    }
    else{
      // Animate between maps
      this->animateFromPlayerToPlayer(this->activePlayer, this->opponentPlayer, true);

      // Do a turn while AI has shots
      for (uint8_t i = 0; i < this->opponentPlayer->getCharacterData()->numberOfShots; i++) {
        this->runAITurn();

        // check if player has won
        gameOver = this->activePlayer->numberOfRemainingShips() <= 0;

        // break if player has won
        if (gameOver) break;
      }
    }

    // next player
    this->playerFirstRound = !this->playerFirstRound;
  }

  return BAGameCommandNext;
}

// =============================================
// Game rounds

void BAGame::runPlayerTurn(){

  // store information
  ABPoint playerCursor = ABPointMake(6, 4);
  ABPoint selectedTargetTile = ABPointMake(-1, -1);
  bool targetLocked = false;
  bool cursorFlip = true;
  uint8_t menuIdx = 0;

  // Game loop
  while(true){
    if (!this->arduboy.nextFrame()) continue;
    if (this->arduboy.everyXFrames(10)) cursorFlip = !cursorFlip;

    // handle input
    this->input->updateInput();

    if(this->input->pressed(RIGHT_BUTTON)){
      playerCursor.x++;

      // limit
      int maxX = BAPlayer::gameBoardSize().width - 1;
      playerCursor.x = ((playerCursor.x > maxX)? maxX : playerCursor.x);
    }
    if(this->input->pressed(LEFT_BUTTON)){
      playerCursor.x--;

      // limit
      if (targetLocked)
        playerCursor.x = ((playerCursor.x < 0)? -1 : playerCursor.x); // -1 is okay for menu
      else
        playerCursor.x = ((playerCursor.x < 0)? 0 : playerCursor.x);
    }
    if(this->input->pressed(UP_BUTTON)){
      playerCursor.y--;

      // limit
      playerCursor.y = ((playerCursor.y < 0)? 0 : playerCursor.y);

      if(playerCursor.x < 0)
        menuIdx = (menuIdx+1)%2;

    }
    if(this->input->pressed(DOWN_BUTTON)){
      playerCursor.y++;

      // limit
      int maxY = BAPlayer::gameBoardSize().height - 1;
      playerCursor.y = ((playerCursor.y > maxY)? maxY : playerCursor.y);

      if(playerCursor.x < 0)
        menuIdx = (menuIdx+1)%2;
    }
    if(this->input->pressed(A_BUTTON)){
      if (targetLocked) {
        targetLocked = false;
        playerCursor = selectedTargetTile;
        selectedTargetTile = ABPointMake(-1, -1);
      }
    }
    if(this->input->pressed(B_BUTTON)){
      // When on map, lock on Target tile and
      // set cursor to fire button.
      if(playerCursor.x >= 0){
        targetLocked = true;
        selectedTargetTile = playerCursor;
        playerCursor.x = -1;
        menuIdx = 0;
      }
      // this is the menu
      else{
        // Fire Button
        if(menuIdx == 0 && targetLocked){
          // DO SHOOT
          return;
        }
        // Cancel Button
        else if ( menuIdx == 1 && targetLocked){
          targetLocked = false;

          if (ABPointEqualToPoint(selectedTargetTile, ABPointMake(-1, -1)))
            playerCursor = ABPointMake(6, 4);
          else
            playerCursor = selectedTargetTile;

          selectedTargetTile = ABPointMake(-1, -1);
        }
      }
    }

    // ======================
    // Display all

    arduboy.clear();
    static const ABPoint mapOffset = ABPointMake(32, 0);
    // Draw map
    this->drawMapAtPosition(this->opponentPlayer, mapOffset.x, mapOffset.y, false);

    // Draw player Info
    drawText(this->activePlayer->getCharacterData()->name, 0, 0, WHITE, this->arduboy);
    this->arduboy.drawBitmap(0, 8, BAUI_remaining_ships, 30, 8, WHITE);
    char remainingShipsBuffer[3] = {0};
    sprintf (remainingShipsBuffer, "%d", this->activePlayer->numberOfRemainingShips());
    drawText(remainingShipsBuffer, 0, 16, WHITE, this->arduboy);


    //check if cursor is on map
    if (playerCursor.x >= 0) {
      // draw selection with sprites
      this->arduboy.drawBitmap(playerCursor.x*8 + mapOffset.x, playerCursor.y*8 + mapOffset.y, cursorFlip?BAMap_Cursor_01:BAMap_Cursor_02, 8, 8, WHITE);

      // check if a target is locked
      if(targetLocked){
        // Draw cancle button
        this->arduboy.drawBitmap(0, 46, BAUI_fire, 30, 8, WHITE);
        this->arduboy.drawBitmap(0, 56, BAUI_cancel, 30, 8, WHITE);
      }
      else{
        // Info fields
        this->arduboy.drawBitmap(0, 56, BAUI_b_aim, 30, 8, WHITE);
      }

    }
    // Cursor in menu
    else {
      // only if a target is locked
      if(targetLocked){
        // check if Fire button is selected
        if(menuIdx%2 == 0)
          arduboy.drawBitmap(0, 46, BAUI_fire_selected, 30, 8, WHITE);
        else
          arduboy.drawBitmap(0, 46, BAUI_fire, 30, 8, WHITE);

        // check if cancel is selected
        if(menuIdx%2 == 1)
          arduboy.drawBitmap(0, 56, BAUI_cancel_selected, 30, 8, WHITE);
        else
          arduboy.drawBitmap(0, 56, BAUI_cancel, 30, 8, WHITE);
      }
    }

    arduboy.display();
  }

  return;
}

void BAGame::runAITurn(){
  while(true){
    if (!this->arduboy.nextFrame()) continue;

    // handle input
    this->input->updateInput();

    if(this->input->pressed(B_BUTTON) || this->input->pressed(A_BUTTON)) break;

    arduboy.clear();
    this->drawMapAtPosition(this->opponentPlayer, 32, 0, false);
    arduboy.display();
  }
}

// =============================================
// Animation helper
void BAGame::animateFromPlayerToPlayer(BAPlayer *fromPlayer, BAPlayer *toPlayer, bool directionUp){
  unsigned long startTime = millis();
  unsigned long animationDuration = 2000;

  ABPoint startPointFrom  = ABPointMake(32,0);
  ABPoint endPointFrom    = ABPointMake(32, (directionUp?-64:64));

  ABPoint startPointTo    = ABPointMake(32, (directionUp?64:-64));
  ABPoint endPointTo      = ABPointMake(32,0);

  while(true){

    if (!this->arduboy.nextFrame()) continue;

    // calc delta time
    unsigned long deltaTime = MILLIS_SINCE(startTime);

    // finish translation
    if(deltaTime > animationDuration) return;

    // calc progress
    uint8_t progress = (uint8_t)(deltaTime*100/animationDuration);
    ABPoint progressPointFrom = animatePointFromToPoint(startPointFrom, endPointFrom, progress);
    ABPoint progressPointTo = animatePointFromToPoint(startPointTo, endPointTo, progress);

    // draw
    this->arduboy.clear();

    this->drawMapAtPosition(this->activePlayer, progressPointFrom.x, progressPointFrom.y, true);
    //this->drawMapAtPosition(fromPlayer, progressPointFrom.x, progressPointFrom.y, (fromPlayer == this->activePlayer));
    //this->drawMapAtPosition(toPlayer, progressPointTo.x, progressPointTo.y, (toPlayer == this->activePlayer));

    arduboy.display();
  }
}
