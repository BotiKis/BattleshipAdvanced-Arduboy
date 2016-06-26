#include "BAGame.h"
#include "BACharAssets.h"

BAGameCommand BAGame::showVersusScreen(){
  // for animating stuff
  unsigned long startTime =  millis();
  bool animationFlip = true;

  uint16_t player1AppearAfter = 100;
  uint16_t player2AppearAfter = 300;

  // Show player rect
  ABRect startRect = ABRectMake(-48,0,48,64);
  ABRect endRect = ABRectMake(176,0,48,64);

  //VS Rect
  uint16_t vsAppearsAfter = 600;
  ABRect vsRectStart = ABRectMake(0,-32,128,128);
  ABRect vsRectEnd = ABRectMake(64,32, 1,1);

  // main loop
  while(true){
    if (!this->arduboy.nextFrame()) continue;
    if (this->arduboy.everyXFrames(10)) animationFlip = !animationFlip;

    this->arduboy.clear();

    // update input
    this->input->updateInput();

    // Get Input
    if(this->input->pressed(B_BUTTON)){
      return BAGameCommandNext;
    }
    if(this->input->pressed(A_BUTTON)){
      return BAGameCommandBack;
    }

    // get time
    unsigned long deltatime = MILLIS_SINCE(startTime);
    deltatime = deltatime%5000; // this repeats the animation every 5 seconds

    // draw player 1
    if ( ((uint16_t)deltatime) > player1AppearAfter){
       this->arduboy.drawBitmap(8, 32, BACharacterData::outlineAssetForCharacter(this->activePlayer->getCharacterData()->characterID), 32, 32, WHITE);
       drawText(this->activePlayer->getCharacterData()->name, 8, 10, WHITE, this->arduboy);
    }

    // draw enemy
    if ( ((uint16_t)deltatime) > player2AppearAfter){
      this->arduboy.drawBitmap(92, 32, BACharacterData::outlineAssetForCharacter(this->opponentPlayer->getCharacterData()->characterID), 32, 32, WHITE);
      drawText(this->opponentPlayer->getCharacterData()->name, 92, 10, WHITE, this->arduboy);
    }

    // Draw appear player rect
    // clac progress
    uint16_t progress = ((uint16_t)deltatime)/5;
    progress = (progress > 100)?100:progress;

    ABRect animationRect = animateRectToRect(startRect, endRect, progress);
    this->arduboy.fillRect(animationRect.origin.x, animationRect.origin.y, animationRect.size.width, animationRect.size.height, WHITE);


    // draw VS
    if ( ((uint16_t)deltatime) > vsAppearsAfter ){
      progress = (float)(deltatime - vsAppearsAfter)/3;
      progress = (progress > 100)?100:progress;

      animationRect = animateRectToRect(vsRectStart, vsRectEnd, progress);
      this->arduboy.fillRect(animationRect.origin.x, animationRect.origin.y, animationRect.size.width, animationRect.size.height, WHITE);

      this->arduboy.drawBitmap(50, 16, BACharAsset_VS, 32, 32, WHITE);
    }

    // draw press button
    if ( (MILLIS_SINCE(startTime) > 1000) && animationFlip) {
      drawText("Press A", 43, 56, WHITE, this->arduboy);
    }

    this->arduboy.display();
  }
}
