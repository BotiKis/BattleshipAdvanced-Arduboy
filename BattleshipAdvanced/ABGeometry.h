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

inline bool ABRectContainsPoint ( ABRect rect, ABPoint point ){
  return (/*Horizontal*/ (point.x >= rect.origin.x && point.x <= ABRectMaxX(rect)) && /*Vertical*/ (point.y >= rect.origin.y && point.y <= ABRectMaxY(rect)));
}

inline bool ABRectIntersectsRect ( ABRect rect1, ABRect rect2 ){
  return (rect1.origin.x < ABRectMaxX(rect2) && ABRectMaxX(rect1) > rect2.origin.x && rect1.origin.y < ABRectMaxY(rect2) && ABRectMaxY(rect1)> rect2.origin.y);
}

#endif
