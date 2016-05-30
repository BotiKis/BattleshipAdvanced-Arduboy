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


// ===========================================================
// Char Data 
struct BACharacterData{
    // Char name
    char name[10];

    // ID for artwork
    CharacterID characterID;

    // number of shots
    byte shots;

    // number of ships in every size
    byte sShips;
    byte mShips;
    byte lShips;

    // aim dificulty
    CharDifficulty difficulty;
};

inline BACharacterData BACharacterDataMake(const char *charName, CharacterID charID, byte charShoots, byte charSShips, byte charMShips, byte charLShips, CharDifficulty charDifficulty){
  BACharacterData character;

  strcpy(character.name, charName);
  character.characterID = charID;
  character.shots = charShoots;
  character.sShips = charSShips;
  character.mShips = charMShips;
  character.lShips = charLShips;
  character.difficulty = charDifficulty;

  return character;
}


// ===========================================================
// Player Char

class BAPlayer{
  public:
    BAPlayer(BACharacterData data);
    ~BAPlayer();
    
    // Getter for char data
    BACharacterData getCharacterData();

    // board
    int playerBoard[GAME_BOARD_SIZE_HEIGHT][GAME_BOARD_SIZE_WIDTH];

    // ships
    byte numberOfShips; // includes the destroyed ones
    BAShip shipAtIndex(byte idx);
    byte numberOfRemainingShips();
    
  private:
    // Chardata is not allowed to be modified
    BACharacterData charData;
    BAShip *ships;
};

#endif
