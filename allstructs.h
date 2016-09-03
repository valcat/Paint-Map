#ifndef ALLSTRUCTS_H
#define ALLSTRUCTS_H

typedef struct Point
{
  int x;
  int y;
} Point;

typedef struct Rectangle
{
  Point point;
  int width;
  int height;
} Rectangle;

typedef struct Button
{
  Rectangle rect;
  /* triangle */
  Point first_point;
  Point sec_point;
  Point third_point;
  /* line */
  Point point_line_first;
  Point point_line_sec;
  /* circle */
  Point point_circle;
  int radius;
  int num_segments;
} Button;

typedef enum Drawing_state 
{
  DRAWING_TRIANGlE,
  DRAWING_RECT,
  DRAWING_CIRCLE,
  DRAWING_LINE,
  DEFAULT_STATE
} Drawing_state;

typedef struct Panel_border
{
  Rectangle rect;
} Panel_border;

typedef enum Figure 
{
  RECTANGLE, TRIANGLE, LINE, CIRCLE
} Figure;

typedef enum StartDrawingLine
{
  YES
}StartDrawingLine;

typedef struct MapState
{
  int window_width;
  int window_height;
  int x_passive_motion;
  int y_passive_motion;
  Drawing_state drawing_state;
  StartDrawingLine startDrawingLine;
  Point* point;
  Panel_border* border;
  Button* button_rect;
  Button* button_triangle;
  Button* button_line;
  Button* button_circle;
  Linked_list* points_storage;
} MapState;


#endif