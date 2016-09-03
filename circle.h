#ifndef CIRCLE_H
#define CIRCLE_H
#include "allstructs.h"

extern const int X_CRL;
extern const int Y_CRL;
extern const int RADS;
extern const int NUM_SGMTS;
extern const int SEGMENT;


Button* createButtonCircle(int x, int y, int radius, int num_segments);
Button* initCircle();
void drawCircleButton(Button* button_circle);
void drawCircle(int x, int y, int radius);
void ShineCircleIfMouseOnPoint(int x, int y, int radius);

#endif