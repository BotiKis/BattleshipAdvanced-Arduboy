#include "BAGame.h"
#include "BACharAssets.h"

//16x16
PROGMEM const unsigned char BA_VERSUS_ANIM_TILE[] = {
0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f,
0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00
};

BAGameCommand BAGame::showVersusScreen(){
  // for animating stuff
  unsigned long startTime =  millis();
  bool animationFlip = true;

  uint16_t player1AppearAfter = 100;
  uint16_t player2AppearAfter = 300;

  // Origins for swipe animation
  ABPoint startOrigin = ABPointMake(-32,0);
  ABPoint endOrigin = ABPointMake(192,0);

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

    // animate swipe. Bitmap uses less flash than calling Arduboy::fillRect()
    ABPoint tileAnimationOrigin = animatePointFromToPoint(startOrigin, endOrigin, progress);
    this->arduboy.drawBitmap(tileAnimationOrigin.x   ,  0, BA_VERSUS_ANIM_TILE, 16, 16, WHITE);
    this->arduboy.drawBitmap(tileAnimationOrigin.x-4 , 16, BA_VERSUS_ANIM_TILE, 16, 16, WHITE);
    this->arduboy.drawBitmap(tileAnimationOrigin.x-8 , 32, BA_VERSUS_ANIM_TILE, 16, 16, WHITE);
    this->arduboy.drawBitmap(tileAnimationOrigin.x-12, 48, BA_VERSUS_ANIM_TILE, 16, 16, WHITE);

    this->arduboy.drawBitmap(tileAnimationOrigin.x+12 ,  0, BA_VERSUS_ANIM_TILE, 16, 16, WHITE);
    this->arduboy.drawBitmap(tileAnimationOrigin.x+10 , 16, BA_VERSUS_ANIM_TILE, 16, 16, WHITE);
    this->arduboy.drawBitmap(tileAnimationOrigin.x+4  , 32, BA_VERSUS_ANIM_TILE, 16, 16, WHITE);
    this->arduboy.drawBitmap(tileAnimationOrigin.x+0  , 48, BA_VERSUS_ANIM_TILE, 16, 16, WHITE);

    // draw VS
    if ( ((uint16_t)deltatime) > player2AppearAfter+50 ){
      progress = (float)(deltatime - player2AppearAfter + 50)/3;
      progress = (progress > 100)?100:progress;

      this->arduboy.drawBitmap(50, 16, BACharAsset_VS, 32, 32, WHITE);
    }

    // draw press button
    if ( (MILLIS_SINCE(startTime) > 1000) && animationFlip) {
      drawText("Press A", 43, 56, WHITE, this->arduboy);
    }

    this->arduboy.display();
  }
}
