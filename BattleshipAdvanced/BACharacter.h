#ifndef BACHARACTER_H
#define BACHARACTER_H
#include <Arduboy.h>
#include "BAGlobal.h"

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

class BAPlayer{
  public:
    BAPlayer(BACharacterData data);
    // Getter for char data
    BACharacterData getCharacterData();

    // board
    char playerBoard[GAME_BOARD_SIZE_HEIGHT][GAME_BOARD_SIZE_WIDTH];
  private:
    // Chardata is not allowed to be modified
    BACharacterData charData;
};

#endif
