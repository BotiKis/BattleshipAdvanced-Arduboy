#include "BAGame.h"

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

void BAGame::run(){

    // Store command for next step
    BAGameCommand nextCommand = BAGameCommandNone;

  // Game loop
  while(true){

    // Handle state
    switch (currentState) {

    // Shows Menu
      default:
      case BAGameStateMenu:{
        nextCommand = showMenu();
        updateCurrentStateWithCommand(nextCommand, BAGameStateCharacterSelection, BAGameStateMenu);
        break;
      }

      // Do Char selection
      case BAGameStateCharacterSelection:{
        nextCommand = showCharSelection();
        updateCurrentStateWithCommand(nextCommand, BAGameStatePlaceShips, BAGameStateMenu);
        break;
      }

      case BAGameStatePlaceShips:{
        nextCommand = showPlaceShips();
        updateCurrentStateWithCommand(nextCommand, BAGameStatePlayerTurn, BAGameStateCharacterSelection);
        break;
      }

      case BAGameStatePlayerTurn:{

        break;
      }

      case BAGameStateAITurn:{

        break;
      }
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
