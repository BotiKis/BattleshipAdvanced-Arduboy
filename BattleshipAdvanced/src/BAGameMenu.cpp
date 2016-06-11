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
    if (!this->arduboy.nextFrame()) continue;

    this->arduboy.clear();

    // --------------------------------
    // udpate input
    this->input->updateInput();

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
    if (this->arduboy.everyXFrames(20)){
      bgAnimator++;
      bgAnimator = bgAnimator%4;
    }

    // draw images
    uint8_t waterOffset = ((bgAnimator == 3)?1:bgAnimator)*2; //animate water back and forth
    this->arduboy.drawBitmap(0, (((bgAnimator%2) == 0)?0:1), BAMenuAssetShip, 112, 64, WHITE);
    this->arduboy.drawBitmap(-waterOffset, 47, BAMenuAssetWaves, 132, 16, BLACK); // Contouring the ship
    this->arduboy.drawBitmap(-waterOffset, 48, BAMenuAssetWaves, 132, 16, WHITE);
    this->arduboy.drawBitmap(0, 0, BAMenuAssetTitle, 50, 10, WHITE);

     // Draw items
    for(byte i = 0; i < MENUITEMS; i++){
      drawText(menuItems[i], MENUPOS_X, MENUPOS_Y*i + MENUMARGIN_TOP, WHITE, this->arduboy);

      // If it's the sound button
      if(menuItems[i] == menuitem_sound){
        drawText((this->arduboy.audio.enabled()?"ON":"OFF"), MENUPOS_X+36, MENUPOS_Y*i + MENUMARGIN_TOP, WHITE, this->arduboy);
      }
    }

    // Draw cursor
    drawText(">", MENUPOS_X-8, selectedItem*MENUPOS_Y + MENUMARGIN_TOP, WHITE, this->arduboy);

    this->arduboy.display();
  }

  return BAGameCommandNone;
}
