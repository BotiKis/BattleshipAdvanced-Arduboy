#include "BASounds.h"
#include "BAGlobal.h"

void playSoundSuccess(){
  arduboy.tunes.tone(800, 10);
}

void playSoundBack(){
  arduboy.tunes.tone(200, 10);
}

void playSoundErr(){
  arduboy.tunes.tone(25, 300);
}
