#ifndef BAMAP_H
#define BAMAP_H
#include "BACharacter.h"

// Types are negative because they will be stored in the player map
// and the ships of the player are also stored there with their indices
typedef enum BAMapTileType{
  BAMapTileTypeWater0 = -4, // Pure white
  BAMapTileTypeWater1,      // set to this it will animate the next 2
  BAMapTileTypeWater2,
  BAMapTileTypeWater3,
  
  BAMapTileTypeMountain = -5,
  
  BAMapTileTypeExplosion1 = -9,
  BAMapTileTypeExplosion2,
  BAMapTileTypeExplosion3,
  BAMapTileTypeExplosion4,
}
BAMapTye;

// --------------------------------------------------
// Draws the map for the given player
// --------------------------------------------------

void drawMap(BAPlayer *player);

#endif
