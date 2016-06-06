#include "BAGame.h"
#include "BAMenuAssets.h"

#define MENUPOS_X 10
#define MENUPOS_Y 12
#define MENUMARGIN_TOP 38

#define MENUITEMS 2


BAGameCommand BAGame::showMenu(){

// ---------------------
// Data
const char menuitem_newgame[] = "New Game";
const char menuitem_sound[] = "Sound:";

const char* menuItems[] = {menuitem_newgame, menuitem_sound};

byte selectedItem = 0;
byte bgAnimator = 0;

  while(true){
    // Wait for next frame
    if (!arduboy.nextFrame()) continue;

    arduboy.clear();

    // --------------------------------
    // udpate input
    input->updateInput(arduboy);

    // --------------------------------
    // Menu logic
    if(input->pressed(UP_BUTTON)){
      selectedItem--;
    }
    if(input->pressed(DOWN_BUTTON)){
      selectedItem++;
    }

    selectedItem = selectedItem % MENUITEMS;

    if(input->pressed(B_BUTTON)){
      if(menuItems[selectedItem] == menuitem_newgame){
        delay(200);
        //playSoundSuccess();

        return BAGameCommandNext;
      }
      if(menuItems[selectedItem] == menuitem_sound){
        if(arduboy.audio.enabled())
            arduboy.audio.off();
        else
            arduboy.audio.on();
        //playSoundSuccess();
      }
    }

    // animate BG
    if (arduboy.everyXFrames(20)){
      bgAnimator++;
      bgAnimator = bgAnimator%4;
    }

    // draw images
    arduboy.drawBitmap(0, (((bgAnimator%2) == 0)?0:1), BAMenuAssetShip, 112, 64, WHITE);
    arduboy.drawBitmap(-bgAnimator, 47, BAMenuAssetWaves, 132, 16, BLACK); // Contouring the ship
    arduboy.drawBitmap(-bgAnimator, 48, BAMenuAssetWaves, 132, 16, WHITE);
    arduboy.drawBitmap(0, 0, BAMenuAssetTitle, 50, 10, WHITE);

     // Draw items
    for(byte i = 0; i < MENUITEMS; i++){
      arduboy.setCursor(MENUPOS_X, MENUPOS_Y*i + MENUMARGIN_TOP);
      arduboy.print(menuItems[i]);

      // If it's the sound button
      if(menuItems[i] == menuitem_sound){
        arduboy.setCursor(MENUPOS_X+36, MENUPOS_Y*i + MENUMARGIN_TOP);
        arduboy.print(arduboy.audio.enabled()?"ON":"OFF");
      }
    }

    // Draw cursor
    arduboy.setCursor(MENUPOS_X-8, selectedItem*MENUPOS_Y + MENUMARGIN_TOP);
    arduboy.print(">");

    arduboy.display();
  }

  return BAGameCommandNone;
}
