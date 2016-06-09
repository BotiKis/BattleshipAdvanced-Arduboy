#ifndef GAME_H
#define GAME_H
#include <Arduboy.h>
#include "BAInput.h"
#include "BAUI.h"
#include "ABGeometry.h"
#include "BACharacter.h"

typedef enum BAGameState{
  BAGameStateMenu = 0,
  BAGameStateCharacterSelection,
  BAGameStatePlaceShips,
  BAGameStatePlayerTurn,
  BAGameStateAITurn
}BAGameState;

typedef enum BAGameCommand{
  BAGameCommandError = -1,
  BAGameCommandNone = 0,
  BAGameCommandNext,
  BAGameCommandBack
}BAGameCommand;


class BAGame{
  public:
    BAGame();

    // ======================
    // Methods

    /// starts the game and calls all methods in neccesary order
    void run();


private:
    // ======================
    // Methods

    BAGameCommand showMenu();
    BAGameCommand showCharSelection();
    BAGameCommand showPlaceShips();

    void startNewGame();

    // Stte machine
    void updateCurrentStateWithCommand(BAGameCommand gameCommand, BAGameState nextState, BAGameState previousState);

    // ======================
    // Data
    Arduboy arduboy;
    BAGameState currentState;
    BAInput *input;

    BAPlayer *activePlayer;
    BAPlayer *opponentPlayer;
};
#endif
