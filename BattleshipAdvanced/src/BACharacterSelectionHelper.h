#ifndef CHARSELECTIONHELPER_H
#define CHARSELECTIONHELPER_H
#include <Arduboy.h>
#include "ABGeometry.h"
#include "BACharacter.h"
#include "BACharAssets.h"

void drawCharacterSelectionAsset(BACharacterData character, ABPoint offset){
   ABRect frame;
   frame.origin.x = offset.x;
   frame.origin.y = offset.y;
   frame.size.width = 32;
   frame.size.height = 32;

  // draw char bitmaps
   arduboy.drawBitmap(frame.origin.x, frame.origin.y, fillAssetForCharacter(character.characterID), frame.size.width, frame.size.height, BLACK);
   arduboy.drawBitmap(frame.origin.x, frame.origin.y, outlineAssetForCharacter(character.characterID), frame.size.width, frame.size.height, WHITE);

  // draw name
   frame.size.width = 30;
   frame.size.height = 9;
   frame.origin.x = 34 + offset.x;
   frame.origin.y = 20 + offset.y;
   arduboy.fillRect(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height, BLACK);
   arduboy.setCursor(frame.origin.x+1, frame.origin.y+1);
   arduboy.print(character.name);
}


// --------------------------------------------------
// Selection hihlight
// --------------------------------------------------
void drawSelection(ABPoint offset, byte animator){
  bool selectionFlip = animator%2;
  
   const int padding = 1;
   ABRect frame;
   frame.origin.x = ( ((selectionFlip) ? padding : 0) + offset.x);
   frame.origin.y = ( ((selectionFlip) ? padding : 0) + offset.y);
   frame.size.width = 64 - ((selectionFlip) ? (padding*2) : 0);
   frame.size.height = 32 - ((selectionFlip) ? (padding*2) : 0);

    arduboy.drawRect(frame.origin.x, frame.origin.y, frame.size.width, frame.size.height, WHITE);
}

// --------------------------------------------------
// Draw animated BG
// --------------------------------------------------
void drawTriangles(ABPoint offset, byte animator){
  animator = animator%3;
  
  ABPoint origin = ABPointMake(24 + offset.x, 16 + offset.y);
  ABPoint a, b;

  // first triangle
  a = ABPointMake(8 + offset.x + (animator*8), 0 + offset.y);
  b = ABPointMake(24 + offset.x + (animator*8), 0 + offset.y);

  arduboy.fillTriangle(origin.x, origin.y, a.x, a.y, b.x, b.y, WHITE);

  
  // first triangle
  a = ABPointMake(8 + offset.x + (animator*8), 0 + offset.y);
  b = ABPointMake(24 + offset.x + (animator*8), 0 + offset.y);

  arduboy.fillTriangle(origin.x, origin.y, a.x, a.y, b.x, b.y, WHITE);

 // 2nd triangle
  a = ABPointMake(32 + offset.x + (animator*8), 0 + offset.y);
  b = ABPointMake(48 + offset.x + (animator*8), 0 + offset.y);

  arduboy.fillTriangle(origin.x, origin.y, a.x, a.y, b.x, b.y, WHITE);

  
 // 3rd triangle
  a = ABPointMake(64 + offset.x, 0 + offset.y + (animator*8));
  b = ABPointMake(64 + offset.x, 16 + offset.y + (animator*8));

  arduboy.fillTriangle(origin.x, origin.y, a.x, a.y, b.x, b.y, WHITE);

  
 // 4th triangle
  a = ABPointMake(48 + offset.x - (animator*8), 32 + offset.y);
  b = ABPointMake(64 + offset.x - (animator*8), 32 + offset.y);

  arduboy.fillTriangle(origin.x, origin.y, a.x, a.y, b.x, b.y, WHITE);

  
 // 5th triangle
  a = ABPointMake(16 + offset.x - (animator*8), 32 + offset.y);
  b = ABPointMake(32 + offset.x - (animator*8), 32 + offset.y);

  arduboy.fillTriangle(origin.x, origin.y, a.x, a.y, b.x, b.y, WHITE);

  
 // 6th triangle
  a = ABPointMake(0 + offset.x, 16 + offset.y - (animator*8));
  b = ABPointMake(0 + offset.x, 32 + offset.y - (animator*8));

  arduboy.fillTriangle(origin.x, origin.y, a.x, a.y, b.x, b.y, WHITE);
}

#endif
