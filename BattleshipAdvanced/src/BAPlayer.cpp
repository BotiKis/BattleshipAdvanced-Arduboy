#include "BAPlayer.h"
#include "BAShip.h"
#include "BAMapData.h"
#include "ABGeometry.h"


BAPlayer::BAPlayer(CharacterID charID){
  charData = BACharacterData::newCharacterForID(charID);

  // init ships
  /*
  ships = NULL;
  numberOfShips = charData.numberOfSmallShips + charData.numberOfMediumShips + charData.numberOfLargeShips;
  ships = (BAShip*)malloc(numberOfShips * sizeof(BAShip));//ew BAShip[numberOfShips];
*/
  /*
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
  */
}

BAPlayer::~BAPlayer(){
  delete this->charData;

  free(ships);
  ships = NULL;
}

const BACharacterData* BAPlayer::getCharacterData(){
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

int8_t BAPlayer:: numberOfRemainingShips(){
  byte nr = 0;

  for(int i = 0; i<numberOfShips ;i++)
    if(!BAShipIsShipDestroyed(ships[i])) nr++;

  return nr;
}
