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
#include "graph.h"

const int WIDTH_WINDOW = 1000;
const int HEIGHT_WINDOW = 1000;
const int PANEL_BORD_PADDING = 60;
const char* WINDOW_NAME = "CAT-MAP";
const int MIN_HEIGHT_WINDOW = 700;
const int side_of_figure = 20;
const int STEP = 20;
/* initial coordinates of border */
const int X_BORD = 0;
const int Y_BORD = 0;
const int WIDTH_BORD = 60;

MapState mapState;
void draw(void);
void saveEdges();


Panel_border* createPanelBorder(int x, int y, int width)
{
  mapState.border = malloc(sizeof(Panel_border));
  mapState.border->rect.point.x = x;
  mapState.border->rect.point.y = y;
  mapState.border->rect.width = width;

  return mapState.border;
}

void init(void)
{
  mapState.border = createPanelBorder(X_BORD, Y_BORD, WIDTH_BORD);
  mapState.button_rect = initRect();
  mapState.button_triangle = initTriangle();
  mapState.button_line = initLine();
  mapState.button_circle = initCircle();
  
  mapState.points_storage = createLinkedList();
  mapState.edges_storage = createLinkedList();
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
  }
  /* horizontal lines */
  for (y = 0; y < mapState.window_height; y += STEP) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(0, y);
      glVertex2d(mapState.window_width, y);
    glEnd();
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
}

void drawButtons(void)
{
  drawRectangleButton(mapState.button_rect);
  drawTriangleButton(mapState.button_triangle);
  drawLineButton(mapState.button_line);
  drawCircleButton(mapState.button_circle);
}

void savePoint(int button, int state, int x, int y)
{ 
  Point* point;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    point = malloc(sizeof(Point));
    point->x = x;
    point->y = y;
    addNode(mapState.points_storage, point);
  }
}

void drawPoints(void)
{
  size_t number_of_nodes = count(mapState.points_storage);
  size_t count = 0;
  Node* indexNode = mapState.points_storage->head;
  Point* point1;
  Point* point2;

  if (number_of_nodes > 1) {
    while (indexNode) {   
      point1 = indexNode->element;
      
      if (count < number_of_nodes - 1) {
        point2 = indexNode->next->element;
      }
      drawCircle(point1->x, point1->y, 5);
      count++;  
      indexNode = indexNode->next; 
    }
  }   
}

void saveEdgeToLinkedList(Point* point1, Point* point2)
{
  Edge* edge;
  edge = createEdge(point1, point2);
  addNode(mapState.edges_storage, edge);
}

void checkPreviousPoint(int x, int y)
{
  Point* point;

  point = malloc(sizeof(Point));
  point->x = x;
  point->y = y;
  if (mapState.previous_point != NULL) {
    saveEdgeToLinkedList(mapState.previous_point, point);
  }
  mapState.previous_point = point;
}

void check(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    if (mapState.pressed_key == 1) {
      mapState.previous_point = NULL;
      mapState.pressed_key = 0;
    } else {
      checkPreviousPoint(x, y);
    }
  }
}

void drawEdges()
{
  Node* indexNode = mapState.edges_storage->head;
  Edge* edge;

  while (indexNode) {  
    edge = indexNode->element; 
    drawingLine(edge->point1->x, edge->point1->y, edge->point2->x, edge->point2->y);
    indexNode = indexNode->next; 
  }
}

void motionPassive(int x, int y) 
{
  mapState.x_passive_motion = x;
  mapState.y_passive_motion = mapState.window_height - y;
  glutPostRedisplay();
}

void checkPoint()
{
  size_t number_of_nodes = count(mapState.points_storage);
  size_t count = 0;
  Node* indexNode = mapState.points_storage->head;
  Point* point;
  int step = 3;

  if (number_of_nodes >= 1) {
    while (indexNode) {
      point = indexNode->element;
      if ((mapState.x_passive_motion <= point->x + step && mapState.x_passive_motion >= point->x - step) 
      && (mapState.y_passive_motion <= point->y + step && mapState.y_passive_motion >= point->y - step)) {
        ShineCircleIfMouseOnPoint(point->x, point->y, 8);
        mapState.isCursorOnPoint = YES;
      }
      count++;
      indexNode = indexNode->next;
    }
  }
}

void passiveLineMotion() 
{
  size_t number_of_nodes = count(mapState.points_storage);
  Node* indexNode = mapState.points_storage->head;
  Point* point1;

  if ((mapState.DrawingLine == START) && (number_of_nodes >= 1)) {
    point1 = (Point*)getByIndex(mapState.points_storage, number_of_nodes - 1);
    //drawingLine(point1->x, point1->y, mapState.x_passive_motion, mapState.y_passive_motion);
  }
}


/* function that draws window with all stuff */
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  /* draw working window and panel with set of tools */
  drawGrid();
  drawPanel(mapState.border);
  glColor3f(0, 0, 0);
  drawBitmapText("Tools", 2, 680);
  drawButtons();
  passiveLineMotion();
  checkPoint();
  drawPoints();
  drawEdges();
  glutSwapBuffers();
  glFlush();
}

/* check what button was pressed */
Figure checkCollision(int x, int y)
{
  Figure figure;
  if (y > mapState.button_rect->rect.point.y && y < (mapState.button_rect->rect.point.y + side_of_figure)) {
    figure = RECTANGLE;
  } else if (y > mapState.button_triangle->sec_point.y && y < mapState.button_triangle->first_point.y) {
    figure = TRIANGLE;
  } else if (y > mapState.button_line->point_line_first.y && y < mapState.button_line->point_line_sec.y) {
    figure = LINE;
  } else if(y > mapState.button_circle->point_circle.y - (side_of_figure / 2) 
    && y < mapState.button_circle->point_circle.y + (side_of_figure / 2)) {
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
  int count = 0;
  int new_y = mapState.window_height - y;
  int a;
  a = (x > 60);
  initFlag(x, new_y);

  if (mapState.drawing_state == DRAWING_RECT && a) {
    drawRectangle(x, new_y);
  } else if (mapState.drawing_state == DRAWING_CIRCLE && a) {
    drawCircle(x, new_y, 10);
  } else if (mapState.drawing_state == DRAWING_LINE && a) {
    savePoint(button, state, x, new_y);
    check(button, state, x, new_y);
    mapState.DrawingLine = START;
    draw();
  }
}

void key(int key, int x, int y) 
{
  switch (key) 
  {    
    case 101: 
      mapState.pressed_key = 1;
      break;
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
  //glutMotionFunc();
  glutPassiveMotionFunc(motionPassive);
  glutSpecialFunc(key);
  glutMainLoop();
  free(mapState.border);
  free(mapState.button_rect);
  free(mapState.button_triangle);
  free(mapState.button_line);
  free(mapState.button_circle);
  free(mapState.points_storage);
  free(mapState.edges_storage);

  return 0;
}