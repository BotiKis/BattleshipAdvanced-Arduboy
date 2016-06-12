#ifndef BAPLAYER_H
#define BAPLAYER_H
#include <Arduboy.h>

#include "BACharacter.h"
#include "BAShip.h"


// In 8x8 blocks
#define GAME_BOARD_SIZE_WIDTH 12
#define GAME_BOARD_SIZE_HEIGHT 8

// ===========================================================
// Player Class

class BAPlayer{
  public:
    BAPlayer(BACharacterData data);
    ~BAPlayer();

    // Getter for char data
    BACharacterData getCharacterData();

    // board
    int8_t playerBoard[GAME_BOARD_SIZE_HEIGHT][GAME_BOARD_SIZE_WIDTH];

    // ships
    int8_t numberOfShips; // includes the destroyed ones
    BAShip shipAtIndex(byte idx);
    void   updateShipAtIndex(byte idx, BAShip newShip);
    int8_t numberOfRemainingShips();

  private:
    // Chardata is not allowed to be modified
    BACharacterData charData;
    BAShip *ships;
};

#endif
