#include "BACharacter.h"
#include "BAMap.h"
#include "BACharAssets.h"


const unsigned char* outlineAssetForCharacter(CharacterID characterID){
  switch(characterID){
    default:
    case CharacterIDMatt:   return BACharAsset_characterID1;
    case CharacterIDMimi:   return BACharAsset_characterID2;
    case CharacterIDKenji:  return BACharAsset_characterID3;
    case CharacterIDNaru:   return BACharAsset_characterID4;
  }
}

const unsigned char* fillAssetForCharacter(CharacterID characterID){
  switch(characterID){
    default:
    case CharacterIDMatt:   return BACharAsset_characterID1_Fill;
    case CharacterIDMimi:   return BACharAsset_characterID2_Fill;
    case CharacterIDKenji:  return BACharAsset_characterID3_Fill;
    case CharacterIDNaru:   return BACharAsset_characterID4_Fill;
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

BAPlayer::BAPlayer(BACharacterData data){
  charData = data;

  // init ships
  ships = NULL;
  numberOfShips = charData.numberOfSmallShips + charData.numberOfMediumShips + charData.numberOfLargeShips;
  ships = new BAShip[numberOfShips];

  // small ships
  for(int8_t i = 0; i < charData.numberOfSmallShips; i++)
    ships[i] = BAShipMake(1);

  // medium ships
  for(int8_t i = 0; i < charData.numberOfMediumShips; i++)
    ships[i + charData.numberOfSmallShips] = BAShipMake(2);

  // big ships
  for(int8_t i = 0; i < charData.numberOfLargeShips; i++)
    ships[i + charData.numberOfSmallShips + charData.numberOfMediumShips] = BAShipMake(3);

  // create water map
  for(int8_t j = 0; j < GAME_BOARD_SIZE_HEIGHT; j++){
    for(int8_t i = 0; i < GAME_BOARD_SIZE_WIDTH; i++){
      //Water
      playerBoard[j][i] = BAMapTileTypeWater0;
    }
  }

  // random mountains
  byte mountainsCount = random(3,6);
  ABPoint lastMountainPos = ABPointMake(-1, -1);

  for(byte i = 0; i < mountainsCount ; i++){
    ABPoint mountainPos;
    do{
      mountainPos.x = random(0, GAME_BOARD_SIZE_WIDTH);
      mountainPos.y = random(0, GAME_BOARD_SIZE_HEIGHT);
    }
    while(ABPointEqualToPoint(mountainPos, lastMountainPos));

    lastMountainPos = mountainPos;
    playerBoard[mountainPos.y][mountainPos.x] = BAMapTileTypeMountain;
  }
}

BAPlayer::~BAPlayer(){
  delete ships;
  ships = NULL;
}

BACharacterData BAPlayer::getCharacterData(){
  return charData;
}


BAShip BAPlayer::shipAtIndex(byte idx){
  return ships[idx];
}

void BAPlayer::updateShipAtIndex(byte idx, BAShip newShip){
  ships[idx].remainingLength = newShip.remainingLength;
  ships[idx].horizontal = newShip.horizontal;
  ships[idx].positionX = newShip.positionX;
  ships[idx].positionY = newShip.positionY;
}

byte BAPlayer:: numberOfRemainingShips(){
  byte nr = 0;

  for(int i = 0; i<numberOfShips ;i++)
    if(!BAShipIsShipDestroyed(ships[i])) nr++;

  return nr;
}
