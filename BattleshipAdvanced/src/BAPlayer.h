#ifndef BAPLAYER_H
#define BAPLAYER_H
#include <Arduboy.h>
#include "ABGeometry.h"

#include "BACharacter.h"
#include "BAShip.h"


#define GAME_BOARD_SIZE_WIDTH 12
#define GAME_BOARD_SIZE_HEIGHT 8

// ===========================================================
// Player Class

class BAPlayer{
  public:
    BAPlayer(CharacterID charID);
    ~BAPlayer();

    // Returns the Gameboard size
    static ABSize gameBoardSize();

    // Getter for char data
    const BACharacterData* getCharacterData();

    // board
    int8_t playerBoard[GAME_BOARD_SIZE_HEIGHT][GAME_BOARD_SIZE_WIDTH];

    // ships
    BAShip shipAtIndex(uint8_t idx);
    void   updateShipAtIndex(uint8_t idx, BAShip newShip);
    int8_t numberOfAllShips();
    int8_t numberOfRemainingShips();

    bool shipCollidesOnMap(BAShip &ship);

  private:
    // Chardata is not allowed to be modified
    BACharacterData *charData;
    BAShip *ships; // array of ships
    int8_t numberOfShips; // includes the destroyed ones
};

#endif
