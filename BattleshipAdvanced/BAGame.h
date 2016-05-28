#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <Arduboy.h>
#include "BACharacter.h"

class BAGame{
  public:
    BAGame();

    bool start();

    BACharacterData showCharSelect();
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
