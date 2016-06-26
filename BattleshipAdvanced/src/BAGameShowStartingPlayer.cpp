#include "BAGame.h"
void BAGame::showPrepareForGame(){

  bool animationDone = false;
  bool animationFlip = false;

  unsigned long startTime = millis();

  // screenloop
  while(true){
    if (!this->arduboy.nextFrame()) continue;
    if(this->arduboy.everyXFrames(6)) animationFlip = !animationFlip;

    // handle input
    this->input->updateInput();

    // calc time
    unsigned long deltaTime = MILLIS_SINCE(startTime);

    if(this->input->pressed(A_BUTTON) || this->input->pressed(B_BUTTON)){
      // close screen only after 1 second
      if(animationDone && deltaTime > 1000){
        return;
      }
      else{
        animationDone = true;
      }
    }

    // check if animation should stop
    animationDone = deltaTime > 4000 || animationDone;

    // clear screen
    this->arduboy.clear();

    // write stuff
    drawText("BATTLE BEGINS!", 22, 8, WHITE, this->arduboy);
    drawText("First player:", 25, 26, WHITE, this->arduboy);

    if(animationDone){
      //drawText(this->playerFirstRound ? this->activePlayer->getCharacterData().name: this->opponentPlayer->getCharacterData().name, 49,38, WHITE, this->arduboy);

      // blink continue button
      if(animationFlip)
        drawText("press any button...", 13, 48, WHITE, this->arduboy);
    }
    else
      //drawText( (animationFlip ? this->activePlayer->getCharacterData().name: this->opponentPlayer->getCharacterData().name), 49,38, WHITE, this->arduboy);
    // show
    this->arduboy.display();
  }
}
