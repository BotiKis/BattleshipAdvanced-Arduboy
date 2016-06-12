#include "BACharacter.h"
#include "BACharAssets.h"

const unsigned char* outlineAssetForCharacter(CharacterID characterID){
  switch(characterID){
    default:
    case CharacterIDMatt:   return BACharAsset_characterID1;
    case CharacterIDMimi:   return BACharAsset_characterID2;
    case CharacterIDKenji:  return BACharAsset_characterID3;
    case CharacterIDNaru:   return BACharAsset_characterID4;
    case CharacterIDBoss:   return BACharAsset_characterID4;
  }
}

const unsigned char* fillAssetForCharacter(CharacterID characterID){
  switch(characterID){
    default:
    case CharacterIDMatt:   return BACharAsset_characterID1_Fill;
    case CharacterIDMimi:   return BACharAsset_characterID2_Fill;
    case CharacterIDKenji:  return BACharAsset_characterID3_Fill;
    case CharacterIDNaru:   return BACharAsset_characterID4_Fill;
    case CharacterIDBoss:   return BACharAsset_characterID4_Fill;;
  }
}


BACharacterData BACharacterDataMake(const char *charName, CharacterID charID, byte charShoots, byte charSShips, byte charMShips, byte charLShips, CharDifficulty charDifficulty){
  BACharacterData character;

  strcpy(character.name, charName);
  character.characterID = charID;
  character.numberOfShots = charShoots;
  character.numberOfSmallShips = charSShips;
  character.numberOfMediumShips = charMShips;
  character.numberOfLargeShips = charLShips;
  character.difficulty = charDifficulty;

  return character;
}


uint8_t numberOfAvailableCaharacters(){
  return 4;
}

BACharacterData characterForID(CharacterID characterID){
  // char data
  // name, spriteID, #OfShots per round, small ships, medium ships, large ships, difficulty
  switch(characterID){
    default:
    case CharacterIDMatt:   return BACharacterDataMake("Matt",  CharacterIDMatt,  1, 3, 2, 1, CharDifficultyEasy);
    case CharacterIDMimi:   return BACharacterDataMake("Mimi",  CharacterIDMimi,  1, 5, 2, 1, CharDifficultyHard);
    case CharacterIDKenji:  return BACharacterDataMake("Kenji", CharacterIDKenji, 1, 2, 2, 2, CharDifficultyHard);
    case CharacterIDNaru:   return BACharacterDataMake("Naru",  CharacterIDNaru,  2, 2, 2, 0, CharDifficultyHard);
    case CharacterIDBoss:   return BACharacterDataMake("BOSS",  CharacterIDBoss,  1, 3, 3, 2, CharDifficultyEasy);
  }
}
