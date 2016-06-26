#include "BAGame.h"
void BAGame::showPrepareForGame(){

  bool animationDone = false;
  bool blinkAnimationFlip = false;
  bool selectedPlayerAnimationFlip = false;
  uint8_t timer = 4;

  unsigned long startTime = millis();

  // screenloop
  while(true){
    if (!this->arduboy.nextFrame()) continue;
    if(this->arduboy.everyXFrames(10)) blinkAnimationFlip = !blinkAnimationFlip;
    if(this->arduboy.everyXFrames(15)) timer++;
    if(this->arduboy.everyXFrames(timer)) selectedPlayerAnimationFlip = !selectedPlayerAnimationFlip;

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

    // clear screen
    this->arduboy.clear();

    // write stuff
    drawText("BATTLE BEGINS!", 22, 0, WHITE, this->arduboy);
    drawText("First player:", 25, 10, WHITE, this->arduboy);

    // draw player 1
    this->arduboy.drawBitmap(8, 32, BACharacterData::outlineAssetForCharacter(this->activePlayer->getCharacterData()->characterID), 32, 32, WHITE);
    drawText("You", 12, 22, WHITE, this->arduboy);

    // draw enemy
    this->arduboy.drawBitmap(92, 32, BACharacterData::outlineAssetForCharacter(this->opponentPlayer->getCharacterData()->characterID), 32, 32, WHITE);
    drawText("Enemy", 92, 22, WHITE, this->arduboy);


    // check if animation should stop
    animationDone = deltaTime > 4000 || animationDone;

    bool firstPlayer = animationDone?this->playerFirstRound:selectedPlayerAnimationFlip;

    if(firstPlayer)
      drawText( "<", 44, 42, WHITE, this->arduboy);
    else
      drawText( ">", 82, 42, WHITE, this->arduboy);


    if (animationDone && blinkAnimationFlip) {
      drawText("Press A or B", 28, 56, WHITE, this->arduboy);
    }

    this->arduboy.display();
  }
}
