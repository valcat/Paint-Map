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
#include "edge.h"
#include "find_path.h"

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
const int CIRCLE_DIAMETER = 10;
const int BITMAPTEXT_X = 2;
const int BITMAPTEXT_Y = 680;
const int SIZE_OF_SHINING_CIRCLE = 8;
const int RADIUS_OF_POINT = 5;

MapState mapState;
void draw(void);
int returnIndexOfPoint();

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

Point* createPoint(int x, int y, Linked_list* linked_list, Point* marked_point)
{
  Point* new_point;
  if (marked_point != NULL) {
    new_point = marked_point;
  } else {
    new_point = malloc(sizeof(Point));
    new_point->edges_list = malloc(sizeof(Linked_list));
    new_point->x = x;
    new_point->y = y;
    addNode(linked_list, new_point);
  }
  return new_point;
}

void createEdge(Linked_list* linked_list, Point* new_point, Point* marked_point, Point* previous_point)
{ 
  Edge* edge;
  Point* second_point;

  second_point = new_point;

  if (previous_point != NULL) {

    if (marked_point != NULL) {
      second_point = marked_point;
    } 
    edge = saveEdge(previous_point, second_point);
    addNode(linked_list, edge);
    printf("%p\n", previous_point->edges_list);
    printf("%d %d\n", previous_point->x, previous_point->y);
    addNode(previous_point->edges_list, edge);
    //addNode(second_point->edges_list, edge);

  } else if ((previous_point == NULL) && (mapState.IsCursorOnPoint == true)) {
    previous_point = marked_point;
    edge = saveEdge(previous_point, second_point);
    addNode(linked_list, edge); 
  }
}

void checkSelectedPoint(Linked_list* linked_list, Point* passive_motion_point)
{
  size_t number_of_nodes = count(linked_list);
  size_t count = 0;
  Node* indexNode = linked_list->head;
  Point* point;
  int step = 3;

  if (number_of_nodes >= 1) {
    while (indexNode) {
      point = indexNode->element;
      if ((passive_motion_point->x <= point->x + step && passive_motion_point->x >= point->x - step) 
      && (passive_motion_point->y <= point->y + step && passive_motion_point->y >= point->y - step)) {
        mapState.selected_point = point;
        mapState.IsCursorOnPoint = true;
      }
      count++;
      indexNode = indexNode->next;
    }
  }
}

void markSelectedPoint(Point* previous_point, Point* selected_point, int size_of_circle)
{
  if (mapState.IsCursorOnPoint == true) {

    if (previous_point == NULL) {
      shinePoint(selected_point->x, selected_point->y, size_of_circle);
    } else if (mapState.previous_point->x != selected_point->x) {
      shinePoint(selected_point->x, selected_point->y, size_of_circle);
    }
    mapState.marked_point = selected_point;
    mapState.IsCursorOnPoint = false;
  } else {
    mapState.marked_point = NULL;
  }
}

void motionPassive(int x, int y) 
{
  mapState.passive_motion_point = malloc(sizeof(Point));
  mapState.passive_motion_point->x = x;
  mapState.passive_motion_point->y = mapState.window_height - y;
  glutPostRedisplay();
}

//function is used to draw a line while moving cursor from the one point to find place to click for another point
void passiveLineMotion(Linked_list* linked_list, Point* point1, Point* point2) 
{
  size_t number_of_nodes = count(linked_list);
  Node* indexNode = linked_list->head;

  if ((mapState.DrawingLine == START) && (number_of_nodes != 0)) {
    drawingLine(point1->x, point1->y, point2->x, point2->y);
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
  drawBitmapText("Tools", BITMAPTEXT_X, BITMAPTEXT_Y);
  drawButtons();
  passiveLineMotion(mapState.points_storage, mapState.previous_point, mapState.passive_motion_point);
  drawEdgeVertices(mapState.points_storage, RADIUS_OF_POINT);
  drawEdges(mapState.edges_storage);
  checkSelectedPoint(mapState.points_storage, mapState.passive_motion_point);
  markSelectedPoint(mapState.previous_point, mapState.selected_point, SIZE_OF_SHINING_CIRCLE);
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
  int beginig_of_button_x = 20;
  int end_of_button_x = 40;
  Figure figure;

  if (x > beginig_of_button_x && x < end_of_button_x) {
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
  Point* new_point ;
  a = (x > PANEL_BORD_PADDING);

  initFlag(x, new_y);

  if (mapState.drawing_state == DRAWING_RECT && a) {
    drawRectangle(x, new_y);

  } else if (mapState.drawing_state == DRAWING_CIRCLE && a) {
    drawCircle(x, new_y, CIRCLE_DIAMETER);

  } else if (mapState.drawing_state == DRAWING_LINE && a) {

    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
      mapState.DrawingLine = START;
      mapState.new_point = createPoint(x, new_y, mapState.points_storage, mapState.marked_point);
      createEdge(mapState.edges_storage, mapState.new_point, mapState.marked_point, mapState.previous_point);
      mapState.previous_point = mapState.new_point;
    }  
    draw();
  }
}

void keys(unsigned char key, int x, int y) 
{
  switch (key) 
  {    
    case 27: //ASCII key for Escape
      mapState.previous_point = NULL;
      mapState.DrawingLine = FINISH;
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
  glutPassiveMotionFunc(motionPassive);
  glutKeyboardFunc(keys);
  glutMainLoop();
  free(mapState.border);
  free(mapState.button_rect);
  free(mapState.button_triangle);
  free(mapState.button_line);
  free(mapState.button_circle);
  free(mapState.points_storage);
  free(mapState.edges_storage);
  free(mapState.passive_motion_point);
  free(mapState.new_point);
  free(mapState.new_point->edges_list);
  free(mapState.selected_point);
  free(mapState.marked_point);
  free(mapState.previous_point);

  return 0;
}