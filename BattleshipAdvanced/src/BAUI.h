#ifndef BAUI_H
#define BAUI_H
#include <Arduboy.h>
#include "ABGeometry.h"

// drawstext
void drawText(const char *text, uint8_t x, uint8_t y, uint8_t color, Arduboy &arduboy);

// all 30x9 size

// cancel button
PROGMEM const unsigned char BAUI_cancel[] = {
0xff, 0x01, 0x01, 0x7d, 0x45, 0x45, 0x01, 0x79,
0x25, 0x79, 0x01, 0x7d, 0x09, 0x11, 0x7d, 0x01,
0x7d, 0x45, 0x45, 0x01, 0x7d, 0x55, 0x45, 0x01,
0x7d, 0x41, 0x41, 0x01, 0x01, 0xff, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01
};

PROGMEM const unsigned char BAUI_cancel_selected[] = {
0xff, 0xff, 0xff, 0x83, 0xbb, 0xbb, 0xff, 0x87,
0xdb, 0x87, 0xff, 0x83, 0xf7, 0xef, 0x83, 0xff,
0x83, 0xbb, 0xbb, 0xff, 0x83, 0xab, 0xbb, 0xff,
0x83, 0xbf, 0xbf, 0xff, 0xff, 0xff, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
0x01, 0x01, 0x01, 0x01
};

// place infos
PROGMEM const unsigned char BAUI_a_rotate[] = {
0x7c, 0xfe, 0xff, 0x87, 0xdb, 0x87, 0xff, 0xfe,
0x7c, 0x00, 0x00, 0x7c, 0x34, 0x5c, 0x00, 0x7c,
0x44, 0x7c, 0x00, 0x04, 0x7c, 0x04, 0x00, 0x00,
0x02, 0x22, 0x44, 0xf8, 0x40, 0x20, 0x00, 0x00,
0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00
};

PROGMEM const unsigned char BAUI_b_place[] = {
0x7c, 0xfe, 0xff, 0x83, 0xab, 0x97, 0xff, 0xfe,
0x7c, 0x00, 0x00, 0x7c, 0x14, 0x1c, 0x00, 0x7c,
0x40, 0x40, 0x00, 0x78, 0x24, 0x78, 0x00, 0x7c,
0x44, 0x44, 0x00, 0x7c, 0x54, 0x44, 0x00, 0x00,
0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00
};


PROGMEM const unsigned char BAUI_b_aim[] = {
0x7c, 0xfe, 0xff, 0x83, 0xab, 0x97, 0xff, 0xfe,
0x7c, 0x00, 0x00, 0x78, 0x24, 0x24, 0x78, 0x00,
0x7c, 0x00, 0x7c, 0x08, 0x10, 0x08, 0x7c, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00,
};




#endif