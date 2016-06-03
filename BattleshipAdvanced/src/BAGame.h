#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Arduboy.h>
#include "BACharacter.h"
#include "BAMap.h"

typedef enum BAGamesCommand{
  BAGamesCommandErr =-1,
  BAGamesCommandBack = 0,
  BAGamesCommandNext,
  BAGamesCommandPlayerWon,
  BAGamesCommandAIWon
}
BAGamesCommand;

class BAGame{
  public:
    BAGame();

    // Methods
    bool start();
    void reset();

    // game phases
    BAGamesCommand showCharSelect();
    BAGamesCommand showPositionShips();
    void showFirstPlayer();
    BAGamesCommand playerRound();
    BAGamesCommand enemyRound();

    // animates maps
    void animateFromPlayerToPlayer(BAPlayer *fromPlayer, BAPlayer *toPlayer, bool directionUp);

    // Data
    BAPlayer *player;
    BAPlayer *enemyPlayer;
    bool playerFirstRound;
};



#endif
