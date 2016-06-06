#include "BAGame.h"

// Main game
BAGame *game;

// ---------------------------------------------------
// Setup func
void setup() {
  // put your setup code here, to run once:
  game = new BAGame();
}

// ---------------------------------------------------
// loop func
void loop() {
  game->run();
}
