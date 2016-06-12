#include "BAGame.h"

// -------------------------------------------------------
// Constructor sets up basic stuff for the game

BAGame::BAGame(){
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.initRandomSeed();
  arduboy.audio.on();

  // Start with menu
  currentState = BAGameStateMenu;

  // init input
  input = new BAInput(arduboy);

  activePlayer = NULL;
  opponentPlayer = NULL;
}



// -------------------------------------------------------
// Main game method.
// Handles gamestates and switches to the desired one

void BAGame::run(){

  // Store command for next step
  BAGameCommand nextCommand = BAGameCommandNone;

  // Game loop
  while(true){

    if (currentState == BAGameStateMenu) {
      nextCommand = showMenu();
      updateCurrentStateWithCommand(nextCommand, BAGameStateCharacterSelection, BAGameStateMenu);
    }

    if (currentState == BAGameStateCharacterSelection) {
      nextCommand = showCharSelection();
      updateCurrentStateWithCommand(nextCommand, BAGameStatePlaceShips, BAGameStateMenu);
    }

    if (currentState == BAGameStatePlaceShips) {
      nextCommand = showPlaceShips();
      updateCurrentStateWithCommand(nextCommand, BAGameStatePrepareForGame, BAGameStateCharacterSelection);
    }

    if (currentState == BAGameStatePrepareForGame) {
      // random first player
      this->playerFirstRound = random()%2 == 0;

      // Do preperation logic
      BAGameCommand showPrepareForGame();
      updateCurrentStateWithCommand(BAGameCommandNext, BAGameStatePlaying, BAGameStatePlaceShips);
    }

    if (currentState == BAGameStatePlaying) {
    }
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
