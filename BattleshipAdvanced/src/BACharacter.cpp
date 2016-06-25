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


BACharacterData::BACharacterData(const char *charName, CharacterID charID, byte charShoots, byte charSShips, byte charMShips, byte charLShips, CharDifficulty charDifficulty){
  strcpy(this->name, charName);
  this->characterID = charID;
  this->numberOfShots = charShoots;
  this->numberOfSmallShips = charSShips;
  this->numberOfMediumShips = charMShips;
  this->numberOfLargeShips = charLShips;
  this->difficulty = charDifficulty;
}

BACharacterData::~BACharacterData(){
}

BACharacterData* BACharacterData::newCharacterForID(CharacterID charID){
  // char data
  // name, spriteID, #OfShots per round, small ships, medium ships, large ships, difficulty
  switch(charID){
    default:
    case CharacterIDMatt:   return new BACharacterData("Matt",  CharacterIDMatt,  1, 3, 2, 1, CharDifficultyEasy);
    case CharacterIDMimi:   return new BACharacterData("Mimi",  CharacterIDMimi,  1, 5, 2, 1, CharDifficultyHard);
    case CharacterIDKenji:  return new BACharacterData("Kenji", CharacterIDKenji, 1, 2, 2, 2, CharDifficultyHard);
    case CharacterIDNaru:   return new BACharacterData("Naru",  CharacterIDNaru,  2, 2, 2, 0, CharDifficultyHard);
    case CharacterIDBoss:   return new BACharacterData("BOSS",  CharacterIDBoss,  1, 3, 3, 2, CharDifficultyEasy);
  }
}

uint8_t BACharacterData::numberOfAvailableCharacters(){
  return 4;
}
