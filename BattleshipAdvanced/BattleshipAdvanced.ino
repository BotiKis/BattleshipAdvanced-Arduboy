#include <Arduboy.h>

#include "BAGlobal.h"
#include "BAMenu.h"
#include "BAGame.h"

// Main game
BAGame *game;

// ---------------------------------------------------
// Setup func
void setup() {
  // put your setup code here, to run once:
  arduboy.begin();
  arduboy.setFrameRate(30);
  arduboy.initRandomSeed();
  arduboy.setTextSize(1);
  arduboy.audio.on();

  game = new BAGame();

  resetGame();
}

void resetGame (){
}


// ---------------------------------------------------
// loop func
void loop() {

  showMenu();

  game->start();
}
