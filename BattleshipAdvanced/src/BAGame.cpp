#include "BAGame.h"
#include "MemoryFree.h"
#include "BAUI.h"

// -------------------------------------------------------
// Constructor sets up basic stuff for the game

BAGame::BAGame(){
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.initRandomSeed();
  arduboy.audio.on();

  // init input
  input = new BAInput(&arduboy);

  activePlayer = NULL;
  opponentPlayer = NULL;

  this->printFreeMemoryIndependent();
}

void BAGame::printFreeMemory(){
  char str[10];
  sprintf(str, "%d", freeMemory());
  drawText(str, 0, 0, WHITE, this->arduboy);
}

void BAGame::printFreeMemoryIndependent(){
  // clear screen
  this->arduboy.clear();
  char str[10];
  sprintf(str, "%d", freeMemory());
  drawText(str, 0, 0, WHITE, this->arduboy);

  // clear screen
  this->arduboy.display();
  delay(2000);
}


// -------------------------------------------------------
// Main game method.
// Handles gamestates and switches to the desired one

void BAGame::run(){

  // Start with menu
  currentState = BAGameStateMenu;

  // Store command for next step
  BAGameCommand nextCommand = BAGameCommandNone;

  // Game loop
  while(true){

    if (currentState == BAGameStateMenu) {
      nextCommand = showMenu();
      updateCurrentStateWithCommand(nextCommand, BAGameStateCharacterSelection, BAGameStateMenu);
    }

    this->printFreeMemoryIndependent();

    if (currentState == BAGameStateCharacterSelection) {
      nextCommand = showCharSelection();
      updateCurrentStateWithCommand(nextCommand, BAGameStateMenu, BAGameStateMenu);
    }

    this->printFreeMemoryIndependent();
/*

    if (currentState == BAGameStatePlaceShips) {
      nextCommand = showPlaceShips();
      updateCurrentStateWithCommand(nextCommand, BAGameStatePrepareForGame, BAGameStateCharacterSelection);
    }

    if (currentState == BAGameStatePrepareForGame) {
      // random first player
      this->playerFirstRound = random()%2 == 0;

      // Do preperation logic
      void showPrepareForGame();
      updateCurrentStateWithCommand(BAGameCommandNext, BAGameStatePlaying, BAGameStatePlaceShips);
    }

    if (currentState == BAGameStatePlaying) {
      BAGameCommand playGame();
      updateCurrentStateWithCommand(BAGameCommandNext, BAGameStateMenu, BAGameStateMenu);
    }
    */
  }

}

// ======================
void BAGame::startNewGame(){

  // chars
  delete activePlayer;
  activePlayer = NULL;
  delete opponentPlayer;
  opponentPlayer = NULL;
}


// -------------------------------------------------------
// Pseudo statemachine handling

void BAGame::updateCurrentStateWithCommand(BAGameCommand gameCommand, BAGameState nextState, BAGameState previousState){

  // reset game data for new game
  if (this->currentState == BAGameStateMenu && gameCommand == BAGameCommandNext) {
    this->startNewGame();
  }

  // Default routing
  if(gameCommand == BAGameCommandNext)
    this->currentState = nextState;
  else if(gameCommand == BAGameCommandBack)
    this->currentState = previousState;
}
