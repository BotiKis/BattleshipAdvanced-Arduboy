#ifndef ABGEOMETRY_H
#define ABGEOMETRY_H
#include <Arduboy.h>

// --------------------------------------------------------------
// Types

typedef struct{
  int x;
  int y;
}ABPoint;

const ABPoint CGPointZero = {0,0};

// --------------------------------------------------------------
// comparisson
static inline bool ABPointEqualToPoint(ABPoint a, ABPoint b){
  return ((a.x == b.x) && (a.y == b.y));
}

// --------------------------------------------------------------
// Factories
static inline ABPoint ABPointMake (int x, int y){
  return {x, y};
}

// --------------------------------------------------------------
// Math helper

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

  result.x = startPoint.x + ((endPoint.x - startPoint.x)*progress)/ 100;
  result.y = startPoint.y + ((endPoint.y - startPoint.y)*progress)/ 100;

  return result;
}

#endif
