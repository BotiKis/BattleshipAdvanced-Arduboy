#ifndef ABGEOMETRY_H
#define ABGEOMETRY_H
#include <Arduboy.h>

// --------------------------------------------------------------
// Types

typedef struct{
  int16_t x;
  int16_t y;
}ABPoint;

typedef struct {
  int16_t width;
  int16_t height;
}ABSize;

typedef struct {
  ABPoint origin;
  ABSize size;
}ABRect;

const ABPoint CGPointZero = {0,0};
const ABSize CGRectZero = {0,0};
const ABRect CGSizeZero = {0,0,0,0};

// --------------------------------------------------------------
// comparisson
static inline bool ABPointEqualToPoint(ABPoint a, ABPoint b){
  return ((a.x == b.x) && (a.y == b.y));
}

static inline bool ABSizeEqualToSize(ABSize a, ABSize b){
  return ((a.width == b.width) && (a.height == b.height));
}

static inline bool ABRectEqualToRect(ABRect a, ABRect b){
  return (ABPointEqualToPoint(a.origin, b.origin) && ABSizeEqualToSize(a.size, b.size));
}

// --------------------------------------------------------------
// Factories
static inline ABPoint ABPointMake (int16_t x, int16_t y){
  ABPoint p;
  p.x = x;
  p.y = y;
  return p;
}


static inline ABSize ABSizeMake (int16_t width, int16_t height){
  ABSize s;
  s.width = width;
  s.height = height;
  return s;
}

static inline ABRect ABRectMake (int16_t originX, int16_t  originY, int16_t width, int16_t height){
  ABRect r;
  r.origin.x = originX;
  r.origin.y = originY;
  r.size.width = width;
  r.size.height = height;
  return r;
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

// returns a point between the start and endpoint where the progress must be between 0 and 100
static inline ABPoint animatePointFromToPoint(ABPoint startPoint, ABPoint endPoint, uint8_t progress){
  ABPoint result;

  result.x = startPoint.x + ((endPoint.x - startPoint.x)*progress)/100;
  result.y = startPoint.y + ((endPoint.y - startPoint.y)*progress)/100;

  return result;
}

// returns a size between the start and endsize where the progress must be between 0 and 100
static inline ABSize animateSizeToSize(ABSize startSize, ABSize endSize, uint8_t progress){
  ABSize result;

  result.width  = startSize.width +  ((endSize.width  - startSize.width)  * progress)/100;
  result.height = startSize.height + ((endSize.height - startSize.height) * progress)/100;

  return result;
}

// returns a rect between the start and endrect where the progress must be between 0 and 100
static inline ABRect animateRectToRect(ABRect startRect, ABRect endRect, uint8_t progress){
  ABRect result;

  result.origin = animatePointFromToPoint(startRect.origin, endRect.origin, progress);
  result.size   = animateSizeToSize(startRect.size, endRect.size, progress);

  return result;
}

#endif
