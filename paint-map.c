#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/glu.h"
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"
#include "allstructs.h"
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "triangle.h"

const int WIDTH_WINDOW = 1000;
const int HEIGHT_WINDOW = 1000;
const int PANEL_BORD_PADDING = 60;
const char* WINDOW_NAME = "CAT-MAP";
const int MIN_HEIGHT_WINDOW = 700;
const int side_of_figure = 20;
const int STEP = 20;
int flag = 0;

int xf, yf, xs, ys;

// TODO: check code style for the name
typedef enum Drawing_state 
{
  DRAWING_TRIANGlE,
  DRAWING_RECT,
  DRAWING_CIRCLE,
  DRAWING_LINE,
  DEFAULT_STATE
} Drawing_state;

typedef struct MapState
{
  int window_width;
  int window_height;
  Drawing_state drawing_state; // flag TODO: create enum for states
} MapState;

MapState mapState;

/* initial coordinates of border */
const int X_BORD = 0;
const int Y_BORD = 0;
const int WIDTH_BORD = 60;

typedef enum Figure 
{
  RECTANGLE, TRIANGLE, LINE, CIRCLE
} Figure;

typedef struct Panel_border
{
  Rectangle rect;
} Panel_border;

Panel_border* border = NULL;
Button* button_rect = NULL;
Button* button_triangle = NULL;
Button* button_line = NULL;
Button* button_circle = NULL;
Linked_list* points_storage = NULL;
Node* piece = NULL;
Point* point = NULL;

Panel_border* createPanelBorder(int x, int y, int width)
{
  Panel_border* border = malloc(sizeof(Panel_border));
  border->rect.point.x = x;
  border->rect.point.y = y;
  border->rect.width = width;

  return border;
}

void init(void)
{
  border = createPanelBorder(X_BORD, Y_BORD, WIDTH_BORD);
  button_rect = initRect();
  button_triangle = initTriangle();
  button_line = initLine();
  button_circle = initCircle();
  
  points_storage = createLinkedList();
}

void reshape(int width, int height)
{
  /* Minimum height is MIN_HEIGHT_WINDOW.
   * Window's size can not be smaller than this value. */
  if (height < MIN_HEIGHT_WINDOW) {
    glutReshapeWindow(mapState.window_width, MIN_HEIGHT_WINDOW);
  }
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  mapState.window_width = width;
  mapState.window_height = height;
}

void drawPanel(Panel_border* border)
{
  int x, y, width, height;
  x = border->rect.point.x;
  y = border->rect.point.y;
  width = border->rect.width;
  height = mapState.window_height;

  glColor3f(0.9, 0.9, 0.9);
  glBegin(GL_QUADS);              
    glVertex2f(x, y);               
    glVertex2f(x + width, y);         
    glVertex2f(x + width, height);  
    glVertex2f(x, height);
  glEnd();
  glFlush();
  glutSwapBuffers();
  printf(" y2 - %d\n", y);
  printf("height - %d\n", height);
}

void drawGrid()
{
  int x, y;

  /* vertical lines */
  for (x = 0; x < mapState.window_width; x += STEP) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x, 0);
      glVertex2d(x, mapState.window_height);
    glEnd();
    glFlush();
  }
  /* horizontal lines */
  for (y = 0; y < mapState.window_height; y += STEP) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(0, y);
      glVertex2d(mapState.window_width, y);
    glEnd();
    glFlush();
  }
}

void drawBitmapText(char *string, int x, int y) 
{  
  char *c;
  glRasterPos2f(x, y);

  for (c = string; *c != '\0'; c++) 
  {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
  }
  glFlush();
  glutSwapBuffers();
}

void drawButtons(void)
{
  drawRectangleButton(button_rect);
  drawTriangleButton(button_triangle);
  drawLineButton(button_line);
  drawCircleButton(button_circle);
}

/* function that draws window with all stuff */
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  /* draw working window and panel with set of tools */
  drawGrid();
  drawPanel(border);
  glColor3f(0, 0, 0);
  drawBitmapText("Tools", 2, 680);
  drawButtons();
  glFlush();
}

void clickOnLine(int button, int state, int x, int y)
{ 
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    point = malloc(sizeof(Point));
    drawCircle(x, y, 5);
    point->x = x;
    point->y = y;
    addNode(points_storage, point);
    size_t number_of_nodes = count(points_storage);

    if (number_of_nodes > 1) {
      piece = getByIndex(points_storage, number_of_nodes - 2);
      Point* indexPoint = (Point*)(piece->element);
      drawLine(indexPoint->x, indexPoint->y, x, y);
    }
  }
}

/* check what button was pressed */
Figure checkCollision(int x, int y)
{
  Figure figure;
  if (y > button_rect->rect.point.y && y < (button_rect->rect.point.y + side_of_figure)) {
    figure = RECTANGLE;
  } else if (y > button_triangle->sec_point.y && y < button_triangle->first_point.y) {
    figure = TRIANGLE;
  } else if (y > button_line->point_line_first.y && y < button_line->point_line_sec.y) {
    figure = LINE;
  } else if(y > button_circle->point_circle.y - (side_of_figure / 2) 
    && y < button_circle->point_circle.y + (side_of_figure / 2)) {
      figure = CIRCLE;
  }

  return figure;
}

void initFlag(int x, int y) 
{
  int beginig_x = 20;
  int end_x = 40;
  Figure figure;

  if (x > beginig_x && x < end_x) {
    figure = checkCollision(x, y);   
  } 
  if (figure == RECTANGLE) {
    mapState.drawing_state = DRAWING_RECT;
  } else if (figure == TRIANGLE) {
    mapState.drawing_state = DRAWING_TRIANGlE;
  } else if (figure == LINE) {
    mapState.drawing_state = DRAWING_LINE;
  } else if (figure == CIRCLE) {
    mapState.drawing_state = DRAWING_CIRCLE;
  }
}

/* draw figure what was chosen from the buttons */
void mouse(int button, int state, int x, int y)
{
  int new_y = mapState.window_height - y;
  int a;
  a = (x > 60);
  initFlag(x, new_y);
  printf("Y -- %d\n", new_y); 
  printf("X -- %d\n", x);

  if (mapState.drawing_state == DRAWING_RECT && a) {
    drawRectangle(x, new_y);
  } else if (mapState.drawing_state == DRAWING_CIRCLE && a) {
    drawCircle(x, new_y, 10);
  } else if (mapState.drawing_state == DRAWING_LINE && a) {
    clickOnLine(button, state, x, new_y);
  }
}

int main(int argc, char *argv[])
{
  init();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(WIDTH_WINDOW, HEIGHT_WINDOW);
  glutInitWindowPosition(0, 0);
  glutCreateWindow(WINDOW_NAME);
  glutDisplayFunc(draw);
  glutReshapeFunc(reshape);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glutMouseFunc(mouse);
  glutMainLoop();
  free(border);
  free(button_rect);
  free(button_triangle);
  free(button_line);
  freeNodes(points_storage);
  free(points_storage);
  free(point);

  return 0;
}