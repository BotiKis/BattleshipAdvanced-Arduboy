#include "BAMenu.h"

#include <Arduboy.h>
#include "BAGlobal.h"
#include "BAMenuAssets.h"

#define MENUPOS_X 10
#define MENUPOS_Y 12
#define MENUMARGIN_TOP 38

// ---------------------
// Funcs
void drawMenu(byte animator);
void updateSelection();

// ---------------------
// Data
const char menuitem_newgame[] = "New Game";
const char menuitem_sound[] = "Sound:";

const char* menuItems[] = {menuitem_newgame, menuitem_sound};

#define MENUITEMS 2

byte selectedItem = 0;

// ---------------------
// Show Menu
void showMenu(){

  // Setup Input class
  byte bgAnimator = 0;

  while(true){
    if (!arduboy.nextFrame()) continue;

    // clear screen
    arduboy.clear();

    // refresh input
    globalInput.updateInput();

    // update selection ui
    updateSelection();

    // handle selection
    if(globalInput.pressed(B_BUTTON)){
      if(menuItems[selectedItem] == menuitem_newgame){
        delay(200);
        playSoundSuccess();
        return;
      }
      if(menuItems[selectedItem] == menuitem_sound){
        if(arduboy.audio.enabled())
            arduboy.audio.off();
        else
            arduboy.audio.on();
        playSoundSuccess();
      }
    }

    // animat BG
    if (arduboy.everyXFrames(20)){
      bgAnimator++;
      bgAnimator = bgAnimator%2;
    }
    
    drawMenu(bgAnimator);
    arduboy.display();
  }
}

// ---------------------
// Funcs
void drawMenu(byte animator){
  // draw BG
   arduboy.drawBitmap(0, 0, ((animator%2) == 0)?BAMenuAssetShip1:BAMenuAssetShip2, 128, 64, WHITE);

   // draw text BG
   arduboy.fillRect(0, MENUMARGIN_TOP - 1, 60, 24, BLACK);

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
}

void updateSelection(){
    if(globalInput.pressed(UP_BUTTON)){
      selectedItem--;
    }
    if(globalInput.pressed(DOWN_BUTTON)){
      selectedItem++;
    }

    selectedItem = selectedItem % MENUITEMS;
}
