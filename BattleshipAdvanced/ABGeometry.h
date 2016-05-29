#ifndef ABGEOMETRY_H
#define ABGEOMETRY_H

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

bool pointIsEqualToPoint(ABPoint a, ABPoint b){
  return ((a.x == b.x) && (a.y == b.y));


bool sizeIsEqualToSize(ABSize a, ABSize b){
  return ((a.width == b.width) && (a.height == b.height));
}

bool rectIsEqualToRect(ABRect a, ABRect b){
  return (pointIsEqualToPoint(a.origin, b.origin) && sizeIsEqualToSize(a.size, b.size));
}


// --------------------------------------------------------------
// Factories

inline ABPoint ABPointMake (int x, int y){
  ABPoint p;
  p.x = x;
  p.y = y;
  return p;
}

inline ABSize ABSizeMake (int width, int height){
  ABSize s;
  s.width = width;
  s.height = height;
  return s;
}

inline ABRect ABSizeMake (int originX, int  originY, int width, int height){
  ABRect r;
  r.origin.x = originX;
  r.origin.y = originY;
  r.size.width = width;
  r.size.height = height;
  return r;
}

// --------------------------------------------------------------
// Math helper

inline bool ABRectMaxX (ABRect rect){
  return rect.origin.x + rect.size.width;
}

inline bool ABRectMaxY (ABRect rect){
  return rect.origin.y + rect.size.height;
}

// Basic collision detection
inline bool ABRectContainsPoint ( ABRect rect, ABPoint point ){
  return (/*Horizontal*/ (point.x >= rect.origin.x && point.x <= ABRectMaxX(rect)) && /*Vertical*/ (point.y >= rect.origin.y && point.y <= ABRectMaxY(rect)));
}

// Basic collision detection
inline bool ABRectIntersectsRect ( ABRect rect1, ABRect rect2 ){
  return (rect1.origin.x < ABRectMaxX(rect2) && ABRectMaxX(rect1) > rect2.origin.x && rect1.origin.y < ABRectMaxY(rect2) && ABRectMaxY(rect1)> rect2.origin.y);
}

// Returns a+b
inline ABPoint addPoints(ABPoint a, ABPoint b){
  ABPointMake(a.x + b.x, a.y + b.y);
}

// Returns a-b
inline ABPoint substractPoints(ABPoint a, ABPoint b){
  ABPointMake(a.x - b.x, a.y - b.y);
}

// --------------------------------------------------------------
// Animators

// returns a point between the start and endpoint where the progress must be between 0 and 1
ABPoint animatePointFromTo(ABPoint startPoint, ABPoint endPoint, float progress){
  ABPoint result;

  result.x = startPoint.x + (int)( ((float)(startPoint.x - endPoint.x))*progress + 0.5f); // 0.5 for correct rounding
  result.y = startPoint.y + (int)( ((float)(startPoint.y - endPoint.y))*progress + 0.5f); // 0.5 for correct rounding
  
  return result;
}

// returns a size between the start and endsize where the progress must be between 0 and 1
ABSize animateSizeToSize(ABSize startSize, ABSize endSize, float progress){
  ABSize result;

  result.width  = startSize.width   + (int)( ((float)(startSize.width - endSize.width))*progress + 0.5f); // 0.5 for correct rounding
  result.height = startSize.height  + (int)( ((float)(startSize.height - endSize.height))*progress + 0.5f); // 0.5 for correct rounding
  
  return result;
}

// returns a rect between the start and endrect where the progress must be between 0 and 1
ABRect animateSizeToSize(ABSize startRect, ABSize endRect, float progress){
  ABRect result;

  result.origin = animatePointFromTo(startRect.origin, endRect.origin, progress);
  result.size   = animateSizeToSize(startRect.size, endRect.size, progress);
  
  return result;
}

#endif
