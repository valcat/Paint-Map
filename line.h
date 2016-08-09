#ifndef LINE_H
#define LINE_H
#include "allstructs.h"

const int X_FST_L;
const int X_SND_L;
const int Y_FST_L;
const int Y_SND_L;

Button* createButtonLine(int x1, int y1, int x2, int y2);
Button* initLine();
void drawLineButton(Button* button_line);
void drawLine(int x1, int y1, int x2, int y2);


#endif