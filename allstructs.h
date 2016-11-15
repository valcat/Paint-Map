#ifndef ALLSTRUCTS_H
#define ALLSTRUCTS_H
#include "linked_list.h"
#include <stdbool.h>

typedef struct Point
{
  int x;
  int y;
  Linked_list* edges_list;
} Point;

typedef struct Rectangle
{
  Point point;
  int width;
  int height;
} Rectangle;

typedef struct Panel_border
{
  Rectangle rect;
} Panel_border;

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

typedef enum Figure 
{
  RECTANGLE, TRIANGLE, LINE, CIRCLE
} Figure;

typedef enum Drawing_state 
{
  DRAWING_TRIANGlE,
  DRAWING_RECT,
  DRAWING_CIRCLE,
  DRAWING_LINE,
  DEFAULT_STATE
} Drawing_state;

typedef enum DrawingLine
{
  START, FINISH
} DrawingLine;


typedef struct Edge
{
  Point* point1;
  Point* point2;    
} Edge;

typedef enum {FALSE = 0, TRUE} boolean;

typedef struct MapState
{
  int window_width;
  int window_height;
  int x_passive_motion;
  int y_passive_motion;
  Drawing_state drawing_state;
  DrawingLine DrawingLine;
  Point* previous_point; // to save the previous point for drawing edges
  Point* point_while_placing_cursor;
  boolean IsCursorOnPoint;
  boolean WasPointShone;
  boolean WasPointSaved;
  Panel_border* border;
  Button* button_rect;
  Button* button_triangle;
  Button* button_line;
  Button* button_circle;
  Linked_list* points_storage;
  Linked_list* edges_storage;
} MapState;


#endif