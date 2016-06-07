#include "BAGame.h"

BAGame::BAGame(){
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.initRandomSeed();
  arduboy.audio.on();

  // Start with menu
  currentState = BAGameStateMenu;

  // init input
  input = new BAInput();

  resetCurrentGameData();
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
void BAGame::resetCurrentGameData(){
}


void BAGame::updateCurrentStateWithCommand(BAGameCommand gameCommand, BAGameState nextState, BAGameState previousState){
  if(gameCommand == BAGameCommandNext)
    currentState = nextState;
  else if(gameCommand == BAGameCommandBack)
    currentState = previousState;
}
