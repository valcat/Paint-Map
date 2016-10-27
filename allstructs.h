#ifndef ALLSTRUCTS_H
#define ALLSTRUCTS_H
#include "linked_list.h"

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

typedef enum DrawingLine
{
  START
} DrawingLine;

typedef enum IsCursorOnPoint
{
  YES
} IsCursorOnPoint;


typedef struct Edge
{
  Point* point1;
  Point* point2;    
} Edge;

typedef struct MapState
{
  int window_width;
  int window_height;
  int x_passive_motion;
  int y_passive_motion;
  int pressed_key;
  Drawing_state drawing_state;
  DrawingLine DrawingLine;
  IsCursorOnPoint isCursorOnPoint;
  Point* previous_point; // to save the previous point for drawing edges
  Panel_border* border;
  Button* button_rect;
  Button* button_triangle;
  Button* button_line;
  Button* button_circle;
  Linked_list* points_storage;
  Linked_list* edges_storage;
  Edge* array;
} MapState;


#endif