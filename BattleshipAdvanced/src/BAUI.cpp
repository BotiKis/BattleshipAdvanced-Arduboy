
#include "BAUI.h"

void drawText(const char *text, uint8_t x, uint8_t y, uint8_t color, Arduboy &arduboy){
  for(byte i = 0; i < strlen(text); i++){
    arduboy.drawChar(x + i*6, y, text[i], color, (color+1)%2, 1);
  }
}
