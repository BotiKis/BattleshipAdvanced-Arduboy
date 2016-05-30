#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Arduboy.h>
#include "BACharacter.h"

typedef enum BAGamesCommand{
  BAGamesCommandErr =-1,
  BAGamesCommandBack = 0,
  BAGamesCommandNext
}
BAGamesCommand;

class BAGame{
  public:
    BAGame();

    // Methods
    bool start();
    void reset();
    BAGamesCommand showCharSelect();

    // Data
    BAPlayer *player;
    BAPlayer *enemyPlayer;
};

/*

typedef enum BAGamestate{
  GamestateMenu = 1,
  GamestateCharSelect,
  GamestateGame,
  GamestateEnd
}
BAGamestate;
*/

#endif
