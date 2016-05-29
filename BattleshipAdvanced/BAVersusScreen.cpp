#include "BAVersusScreen.h"
#include "BAGlobal.h"
#include "ABGeometry.h"
#include "BACharAssets.h"
#include "BAGameAssets.h"

#define VSSCREEN_MILLIS_SINCE(MILLIS) (float)(millis() - MILLIS)
#define VSSCREEN_ANIMATIONTIME 500.0f

BAGamesCommand showVersusScreenWithPlayerAndEnemy(BACharacterData player, BACharacterData enemy){

  // store info
  unsigned long startTime =  millis();

  int player1AppearAfter = 100;
  int player2AppearAfter = 300;

  // Show player rect
  ABRect startRect = ABRectMake(-48,0,48,64);
  ABRect endRect = ABRectMake(167,0,32,64);

  //VS Rect
  int vsAppearsAfter = 600;
  ABRect vsRectStart = ABRectMake(0,-32,128,128);
  ABRect vsRectEnd = ABRectMake(64,32, 1,1);
  
  // main loop
  while(true){
    arduboy.clear();

    // update input
    globalInput.updateInput();

    // get time
    int deltatime = VSSCREEN_MILLIS_SINCE(startTime);

    // draw player 1
    if (deltatime> player1AppearAfter){
       arduboy.drawBitmap(12, 32, outlineAssetForCharacter(player.characterID), 32, 32, WHITE);
       arduboy.setCursor(16,10);
       arduboy.print(player.name);
    }
       
    // draw enemy
    if (deltatime> player2AppearAfter){
       arduboy.drawBitmap(84, 32, outlineAssetForCharacter(enemy.characterID), 32, 32, WHITE);
       arduboy.setCursor(78,10);
       arduboy.print(enemy.name);
    }

    // Draw appear player rect
    // clac progress
    float progress = (float)deltatime/(float)VSSCREEN_ANIMATIONTIME;
    progress = (progress > 1.0f)?1.0f:progress;
  
    ABRect animationRect = animateRectToRect(startRect, endRect, progress);
    arduboy.fillRect(animationRect.origin.x, animationRect.origin.y, animationRect.size.width, animationRect.size.height, WHITE);

    // draw VS
 
    if (deltatime > vsAppearsAfter){
      progress = (float)(deltatime - vsAppearsAfter)/300.0f;
      progress = (progress > 1.0f)?1.0f:progress;
      animationRect = animateRectToRect(vsRectStart, vsRectEnd, progress);
      arduboy.fillRect(animationRect.origin.x, animationRect.origin.y, animationRect.size.width, animationRect.size.height, WHITE);
      
      arduboy.drawBitmap(48, 16, BAGameAsset_VS, 32, 32, WHITE);
    }
    
    // Get Input
    if(globalInput.pressed(A_BUTTON)){
      return BAGamesCommandNext;
    }

    arduboy.display();
  }

  return BAGamesCommandErr;
}

