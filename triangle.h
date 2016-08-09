#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "allstructs.h"

extern const int X_FST_T;
extern const int X_SND_T;
extern const int X_TRD_T;
extern const int Y_FST_T;
extern const int Y_SCD_T;
extern const int Y_TRD_T;

Button* createButtonTriangle(int x1, int y1, int x2, int y2, int x3,  int y3);
Button* initTriangle();
void drawTriangleButton(Button* button_triangle);


#endif