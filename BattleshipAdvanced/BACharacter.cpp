#include "BACharacter.h"
#include "BAMap.h"
#include "BAGlobal.h"

BAPlayer::BAPlayer(BACharacterData data){
  charData = data;

  // init ships
  ships = NULL;
  numberOfShips = charData.sShips + charData.mShips + charData.lShips;
  ships = new BAShip[numberOfShips];

  // small ships
  for(size_t i = 0; i < charData.sShips; i++)
    ships[i] = BAShipMake(BAShipTypeSmall, 1);
    
  // medium ships
  for(size_t i = 0; i < charData.mShips; i++)
    ships[i+charData.sShips] = BAShipMake( BAShipTypeMedium, 2);
    
  // big ships
  for(size_t i = 0; i < charData.lShips; i++)
    ships[i+charData.sShips+charData.mShips] = BAShipMake(BAShipTypeBig, 3);

  // create water map
  for(size_t j = 0; j < GAME_BOARD_SIZE_HEIGHT; j++){
    for(size_t i = 0; i < GAME_BOARD_SIZE_WIDTH; i++){
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
    while(pointIsEqualToPoint(mountainPos, lastMountainPos));
    
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

byte BAPlayer:: numberOfRemainingShips(){
  byte nr = 0;

  for(int i = 0; i<numberOfShips ;i++)
    if(!isShipDestroyed(ships[i])) nr++;

  return nr;
}

