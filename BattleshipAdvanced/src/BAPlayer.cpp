#include "BAPlayer.h"
#include "BAShip.h"
#include "BAMapData.h"
#include "ABGeometry.h"


BAPlayer::BAPlayer(CharacterID charID){


  charData = BACharacterData::newCharacterForID(charID);

  // init ships
  this->ships = new BAShip[charData->numberOfAllShips()];

  // small ships
  for(int8_t i = 0; i < charData->numberOfSmallShips; i++)
    this->ships[i] = BAShipMake(1);

  // medium ships
  for(int8_t i = 0; i < charData->numberOfMediumShips; i++)
    this->ships[i + charData->numberOfSmallShips] = BAShipMake(2);

  // big ships
  for(int8_t i = 0; i < charData->numberOfLargeShips; i++)
    this->ships[i + charData->numberOfSmallShips + charData->numberOfMediumShips] = BAShipMake(3);

  // create water map


// If i uncomment this two loops the game crashes. i dunno why.

/*
  for(int8_t y = 0; y < GAME_BOARD_SIZE_HEIGHT; y++){
    for(int8_t x = 0; x < GAME_BOARD_SIZE_WIDTH; x++){
      //Water
      playerBoard[y][x] = BAMapTileTypeWater0;
    }
  }
*/


/*
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
  */
}

BAPlayer::~BAPlayer(){
  delete this->charData;
  this->charData = NULL;

  delete[] this->ships;
  this->ships = NULL;
}

const BACharacterData* BAPlayer::getCharacterData(){
  return charData;
}

BAShip BAPlayer::shipAtIndex(uint8_t idx){
  return ships[idx];
}

void BAPlayer::updateShipAtIndex(uint8_t idx, BAShip newShip){
  ships[idx].remainingLength = newShip.remainingLength;
  ships[idx].horizontal = newShip.horizontal;
  ships[idx].positionX = newShip.positionX;
  ships[idx].positionY = newShip.positionY;
}

int8_t BAPlayer::numberOfRemainingShips(){
  uint8_t nr = 0;

  for(int i = 0; i<numberOfShips ;i++)
    if(!BAShipIsShipDestroyed(ships[i])) nr++;

  return nr;
}
