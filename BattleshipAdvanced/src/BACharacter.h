#ifndef BACHARACTER_H
#define BACHARACTER_H
#include <Arduboy.h>

typedef enum {
  CharDifficultyEasy = 0,
  CharDifficultyHard
}CharDifficulty;

typedef enum {
  CharacterIDMatt = 0,
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
class BACharacterData{
public:
    // init
    BACharacterData(const char *charName, CharacterID charID, byte charShoots, byte charSShips, byte charMShips, byte charLShips, CharDifficulty charDifficulty);
    ~BACharacterData();

    // Static Factory for char data
    static BACharacterData* newCharacterForID(CharacterID charID); // needs to be deleted
    static uint8_t numberOfAvailableCharacters();

// Data stays public for simplicity - hell i don't want to make accessors
    // Char name
    char name[6];

    // ID for artwork
    CharacterID characterID;

    // number of shots
    uint8_t numberOfShots;

    // number of ships in every size
    uint8_t numberOfSmallShips;
    uint8_t numberOfMediumShips;
    uint8_t numberOfLargeShips;

    uint8_t numberOfAllShips();

    // aim dificulty
    CharDifficulty difficulty;
};

#endif
