#ifndef CIRCLE_H
#define CIRCLE_H

extern const int X_CRL;
extern const int Y_CRL;
extern const int RADS;
extern const int NUM_SGMTS;
extern const int SEGMENT;

typedef struct Point_c
{
  int x;
  int y;
} Point_c;

typedef struct Button_c
{
  Point_c point_circle;
  int radius;
  int num_segments;
} Button_c;

Button_c* createButtonCircle(int x, int y, int radius, int num_segments);
Button_c* initCircle();
void drawCircleButton(Button_c* button_circle);

#endif