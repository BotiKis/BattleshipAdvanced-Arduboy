#ifndef BACHARACTER_H
#define BACHARACTER_H
#include <Arduboy.h>
#include "BAShip.h"

// In 8x8 blocks
#define GAME_BOARD_SIZE_WIDTH 12
#define GAME_BOARD_SIZE_HEIGHT 8

typedef enum {
  CharDifficultyEasy = 0,
  CharDifficultyHard
}CharDifficulty;

typedef enum {
  CharacterIDMatt = 1,
  CharacterIDMimi,
  CharacterIDKenji,
  CharacterIDNaru
}CharacterID;


// Returns the correct bitmap for the requested char
const unsigned char* outlineAssetForCharacter(CharacterID characterID);
const unsigned char* fillAssetForCharacter(CharacterID characterID);


// ===========================================================
// Char Data
struct BACharacterData{
    // Char name
    char name[6];

    // ID for artwork
    CharacterID characterID;

    // number of shots
    byte numberOfShots;

    // number of ships in every size
    byte numberOfSmallShips;
    byte numberOfMediumShips;
    byte numberOfLargeShips;

    // aim dificulty
    CharDifficulty difficulty;
};

// Factory for char data
BACharacterData BACharacterDataMake(const char *charName, CharacterID charID, byte charShoots, byte charSShips, byte charMShips, byte charLShips, CharDifficulty charDifficulty);


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
    byte numberOfShips; // includes the destroyed ones
    BAShip shipAtIndex(byte idx);
    void updateShipAtIndex(byte idx, BAShip newShip);
    byte numberOfRemainingShips();

  private:
    // Chardata is not allowed to be modified
    BACharacterData charData;
    BAShip *ships;
};

#endif
