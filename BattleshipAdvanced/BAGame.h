#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Arduboy.h>
#include "BACharacter.h"
#include "BAMap.h"

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
    BAGamesCommand showPositionShips();

    // Data
    BAPlayer *player;
    BAPlayer *enemyPlayer;
};



#endif
