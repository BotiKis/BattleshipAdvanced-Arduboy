#include "BAPlayer.h"
#include "BAShip.h"
#include "BAMapData.h"
#include "ABGeometry.h"


BAPlayer::BAPlayer(CharacterID charID){

  // init character Data
  this->charData = BACharacterData::newCharacterForID(charID);

  this->numberOfShips = charData->numberOfSmallShips + charData->numberOfMediumShips + charData->numberOfLargeShips;

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

  // create map
  uint8_t mountainsCount = random(4,6);
  for(int8_t y = 0; y < GAME_BOARD_SIZE_HEIGHT; y++){
    for(int8_t x = 0; x < GAME_BOARD_SIZE_WIDTH; x++){
      // Water
      playerBoard[y][x] = BAMapTileTypeWater0;

      // slight chance fo a mountain
      if ( (random(0, 100) < 3) && (mountainsCount > 0) ) {
        playerBoard[y][x] = BAMapTileTypeMountain;
        mountainsCount--;
      }
    }
  }

  // distribute the remaining mountains
  while(mountainsCount > 0) {
    uint8_t x = random(0, GAME_BOARD_SIZE_WIDTH);
    uint8_t y = random(0, GAME_BOARD_SIZE_HEIGHT);

    if (playerBoard[y][x] != BAMapTileTypeMountain) {
      playerBoard[y][x] = BAMapTileTypeMountain;
      mountainsCount--;
    }
  }
}

BAPlayer::~BAPlayer(){
  delete this->charData;
  this->charData = NULL;

  delete[] this->ships;
  this->ships = NULL;
}

ABSize BAPlayer::gameBoardSize(){
  return ABSizeMake(GAME_BOARD_SIZE_WIDTH, GAME_BOARD_SIZE_HEIGHT);
}

const BACharacterData* BAPlayer::getCharacterData(){
  return charData;
}

BAShip BAPlayer::shipAtIndex(uint8_t idx){
  return ships[idx];
}

void BAPlayer::updateShipAtIndex(uint8_t idx, BAShip newShip){
  ships[idx].remainingLength = newShip.remainingLength;
  ships[idx].orientation = newShip.orientation;
  ships[idx].positionX = newShip.positionX;
  ships[idx].positionY = newShip.positionY;
}

int8_t BAPlayer::numberOfAllShips(){
  return this->numberOfShips;
}

int8_t BAPlayer::numberOfRemainingShips(){
  uint8_t nr = 0;

  for(int i = 0; i<this->numberOfAllShips() ;i++)
    if(!BAShipIsShipDestroyed(ships[i])) nr++;

  return nr;
}

bool BAPlayer::shipCollidesOnMap(BAShip &ship){
  bool colides = false;
  for (int len = 0; len < ship.fullLength; len++) {
    int dX = 0, dY = 0;

    if (ship.orientation == BAShipOrientationHorizontal)
      dX = len;
    else
      dY = len;

    if (this->playerBoard[ship.positionY+dY][ship.positionX+dX] >= 0 || this->playerBoard[ship.positionY+dY][ship.positionX+dX] == BAMapTileTypeMountain) {
      colides = true;
      break;
    }
  }

  return colides;
}
