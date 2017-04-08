
#include "BAUI.h"

void drawText(const char *text, uint8_t x, uint8_t y, uint8_t color, Arduboy2 &arduboy){
  for(uint8_t i = 0; i < strlen(text); i++){
    arduboy.drawChar(x + i*6, y, text[i], color, (color+1)%2, 1);
  }
}

void drawTextRightAligned(const char *text, uint8_t x, uint8_t y, uint8_t color, Arduboy2 &arduboy){
  uint8_t len = strlen(text) -1;
  for(uint8_t i = 0; i <= len; i++){
    arduboy.drawChar(x - i*6, y, text[len - i], color, (color+1)%2, 1);
  }
}
