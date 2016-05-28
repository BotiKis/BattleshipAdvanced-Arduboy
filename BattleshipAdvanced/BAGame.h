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

    bool start();

    BAGamesCommand showCharSelect();
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
