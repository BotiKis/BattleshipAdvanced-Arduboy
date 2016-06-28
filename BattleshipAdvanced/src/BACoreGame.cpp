#include "BAGame.h"

BAGameCommand BAGame::playGame(){

  bool gameOver = false;

  while (!gameOver) {
    if(this->playerFirstRound){

      this->animateFromPlayerToPlayer(this->opponentPlayer, this->activePlayer, false);

      for (uint8_t i = 0; i < this->activePlayer->getCharacterData()->numberOfShots; i++) {
        while(true){
          if (!this->arduboy.nextFrame()) continue;

          // handle input
          this->input->updateInput();

          if(this->input->pressed(B_BUTTON) || this->input->pressed(A_BUTTON)) break;

          arduboy.clear();

          this->drawMapAtPosition(this->activePlayer, 32, 0, true);

          arduboy.display();
        }
      }
    }
    else{
      this->animateFromPlayerToPlayer(this->activePlayer, this->opponentPlayer, true);

      for (uint8_t i = 0; i < this->opponentPlayer->getCharacterData()->numberOfShots; i++) {

        while(true){
          if (!this->arduboy.nextFrame()) continue;

          // handle input
          this->input->updateInput();

          if(this->input->pressed(B_BUTTON) || this->input->pressed(A_BUTTON)) break;

          arduboy.clear();
          this->drawMapAtPosition(this->opponentPlayer, 32, 0, false);
          arduboy.display();
        }
      }
    }

    // next player
    this->playerFirstRound = !this->playerFirstRound;
  }

  return BAGameCommandNext;
}


void BAGame::animateFromPlayerToPlayer(BAPlayer *fromPlayer, BAPlayer *toPlayer, bool directionUp){
  unsigned long startTime = millis();
  unsigned long animationDuration = 2000;

  ABPoint startPointFrom  = ABPointMake(32,0);
  ABPoint endPointFrom    = ABPointMake(32, (directionUp?-64:64));

  ABPoint startPointTo    = ABPointMake(32, (directionUp?64:-64));
  ABPoint endPointTo      = ABPointMake(32,0);

  while(true){

    if (!this->arduboy.nextFrame()) continue;

    // calc delta time
    unsigned long deltaTime = MILLIS_SINCE(startTime);

    // finish translation
    if(deltaTime > animationDuration) return;

    // calc progress
    uint8_t progress = (uint8_t)(deltaTime*100/animationDuration);
    ABPoint progressPointFrom = animatePointFromToPoint(startPointFrom, endPointFrom, progress);
    ABPoint progressPointTo = animatePointFromToPoint(startPointTo, endPointTo, progress);

    // draw
    this->arduboy.clear();

    this->drawMapAtPosition(this->activePlayer, progressPointFrom.x, progressPointFrom.y, true);
    //this->drawMapAtPosition(fromPlayer, progressPointFrom.x, progressPointFrom.y, (fromPlayer == this->activePlayer));
    //this->drawMapAtPosition(toPlayer, progressPointTo.x, progressPointTo.y, (toPlayer == this->activePlayer));

    arduboy.display();
  }
}
