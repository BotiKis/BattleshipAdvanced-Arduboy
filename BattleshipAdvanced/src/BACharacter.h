#ifndef BACHARACTER_H
#define BACHARACTER_H
#include <Arduboy.h>

typedef enum {
  CharDifficultyEasy = 0,
  CharDifficultyHard
}CharDifficulty;

typedef enum {
  CharacterIDMatt = 1,
  CharacterIDMimi,
  CharacterIDKenji,
  CharacterIDNaru,
  CharacterIDBoss = -1
}CharacterID;


// Returns the correct bitmap for the requested char
const unsigned char* outlineAssetForCharacter(CharacterID characterID);
const unsigned char* fillAssetForCharacter(CharacterID characterID);


// ===========================================================
// Char Data
typedef struct{
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
}BACharacterData;

// Factory for char data
BACharacterData BACharacterDataMake(const char *charName, CharacterID charID, byte charShoots, byte charSShips, byte charMShips, byte charLShips, CharDifficulty charDifficulty);
BACharacterData characterForID(CharacterID characterID);
uint8_t numberOfAvailableCaharacters();

#endif
