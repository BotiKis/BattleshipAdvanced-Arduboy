#ifndef ABGEOMETRY_H
#define ABGEOMETRY_H
#include <math.h>

// --------------------------------------------------------------
// Types

struct ABPoint{
  int x;
  int y;
};

struct ABSize{
  int width;
  int height;
};

struct ABRect{
  ABPoint origin;
  ABSize size;
};

// --------------------------------------------------------------
// comparisson

static inline bool pointIsEqualToPoint(ABPoint a, ABPoint b){
  return ((a.x == b.x) && (a.y == b.y));
}

static inline bool sizeIsEqualToSize(ABSize a, ABSize b){
  return ((a.width == b.width) && (a.height == b.height));
}

static inline bool rectIsEqualToRect(ABRect a, ABRect b){
  return (pointIsEqualToPoint(a.origin, b.origin) && sizeIsEqualToSize(a.size, b.size));
}


// --------------------------------------------------------------
// Factories

static inline ABPoint ABPointMake (int x, int y){
  return {x, y};
}

static inline ABSize ABSizeMake (int width, int height){
  return {width, height};
}

static inline ABRect ABRectMake (int originX, int  originY, int width, int height){
  return {{originX, originY}, {width, height}};
}

// --------------------------------------------------------------
// Math helper

static inline bool ABRectMaxX (ABRect rect){
  return rect.origin.x + rect.size.width;
}

static inline bool ABRectMaxY (ABRect rect){
  return rect.origin.y + rect.size.height;
}

// Basic collision detection
static inline bool ABRectContainsPoint ( ABRect rect, ABPoint point ){
  return (/*Horizontal*/ (point.x >= rect.origin.x && point.x <= ABRectMaxX(rect)) && /*Vertical*/ (point.y >= rect.origin.y && point.y <= ABRectMaxY(rect)));
}

// Basic collision detection
static inline bool ABRectIntersectsRect ( ABRect rect1, ABRect rect2 ){
  return (rect1.origin.x < ABRectMaxX(rect2) && ABRectMaxX(rect1) > rect2.origin.x && rect1.origin.y < ABRectMaxY(rect2) && ABRectMaxY(rect1)> rect2.origin.y);
}

// Returns a+b
static inline ABPoint addPoints(ABPoint a, ABPoint b){
  return ABPointMake(a.x + b.x, a.y + b.y);
}

// Returns a-b
static inline ABPoint substractPoints(ABPoint a, ABPoint b){
  return ABPointMake(a.x - b.x, a.y - b.y);
}

// --------------------------------------------------------------
// Animators

// returns a point between the start and endpoint where the progress must be between 0 and 1
static inline ABPoint animatePointFromToPoint(ABPoint startPoint, ABPoint endPoint, float progress){
  ABPoint result;

  result.x = startPoint.x + (((float)(endPoint.x - startPoint.x))*progress + 0.5f); // 0.5 for correct rounding
  result.y = startPoint.y + (((float)(endPoint.y - startPoint.y))*progress + 0.5f); // 0.5 for correct rounding
  
  return result;
}

// returns a size between the start and endsize where the progress must be between 0 and 1
static inline ABSize animateSizeToSize(ABSize startSize, ABSize endSize, float progress){
  ABSize result;

  result.width  = startSize.width   + ( ((float)(endSize.width - startSize.width))*progress + 0.5f); // 0.5 for correct rounding
  result.height = startSize.height  + ( ((float)(endSize.height - startSize.height))*progress + 0.5f); // 0.5 for correct rounding
  
  return result;
}

// returns a rect between the start and endrect where the progress must be between 0 and 1
static inline ABRect animateRectToRect(ABRect startRect, ABRect endRect, float progress){
  ABRect result;

  result.origin = animatePointFromToPoint(startRect.origin, endRect.origin, progress);
  result.size   = animateSizeToSize(startRect.size, endRect.size, progress);
  
  return result;
}

#endif
