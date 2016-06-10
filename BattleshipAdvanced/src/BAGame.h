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

// Types are negative because they will be stored in the player map
// and the ships of the player are also stored there with their indices
typedef enum BAMapTileType{
  BAMapTileTypeWater0 = -4, // Pure black
  BAMapTileTypeWater1,      // set to this and it will animate the next 2
  BAMapTileTypeWater2,
  BAMapTileTypeWater3,

  BAMapTileTypeMountain = -5,

  BAMapTileTypeExplosion1 = -9,
  BAMapTileTypeExplosion2,
  BAMapTileTypeExplosion3,
  BAMapTileTypeExplosion4,

  BAMapTileTypeDestroyedShip = -10
}
BAMapTye;


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

    void startNewGame();

    // Game methods
    BAGameCommand showMenu();
    BAGameCommand showCharSelection();
    BAGameCommand showPlaceShips();

    // Helper
    void drawMap(BAPlayer *player, bool showShips);
    void drawMapAtPosition(BAPlayer *player, uint8_t x, uint8_t y, bool showShips);

    // State machine
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
