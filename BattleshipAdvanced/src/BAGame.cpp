#include "BAGame.h"

#define  UDPATE_STATE(COMMAND, NEXTSTATE, PREVSTATE)\
        if(COMMAND == BAGameCommandNext)            \
          currentState = NEXTSTATE;                 \
        else if(COMMAND == BAGameCommandBack)       \
          currentState = PREVSTATE;

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
      default:

      // Shows Menu
      case BAGameStateMenu:{
        nextCommand = showMenu();
        UDPATE_STATE(nextCommand, BAGameStateCharacterSelection, BAGameStateMenu);
        break;
      }

      // Do Char selection
      case BAGameStateCharacterSelection:{
        nextCommand = showCharSelection();
        UDPATE_STATE(nextCommand, BAGameStatePlaceShips, BAGameStateMenu);
        break;
      }

      case BAGameStatePlaceShips:{
        nextCommand = showPlaceShips();
        UDPATE_STATE(nextCommand, BAGameStatePlayerTurn, BAGameStateCharacterSelection);
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
