#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "allstructs.h"

/* rectangle */
extern const int X_RECT;
extern const int Y_RECT;
extern const int WIDTH_RECT;
extern const int HEIGHT_RECT;

Button* initRect();
void drawRectangleButton(Button* button_rect);
void drawRectangle(int x, int y);

#endif