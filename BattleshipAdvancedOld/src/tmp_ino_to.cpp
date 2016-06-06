#include <Arduino.h>
#line 1 "/Users/Boti/Documents/coding/Arduboy/BattleshipAdvanced-Arduboy/BattleshipAdvanced/src/BattleshipAdvanced.ino"
#include <Arduboy.h>

#include "BAGlobal.h"
#include "BAMenu.h"
#include "BAGame.h"

// Main game
BAGame *game;

// ---------------------------------------------------
// Setup func
void setup();

void resetGame ();
void loop();
#line 13 "/Users/Boti/Documents/coding/Arduboy/BattleshipAdvanced-Arduboy/BattleshipAdvanced/src/BattleshipAdvanced.ino"
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