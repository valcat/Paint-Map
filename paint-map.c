#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/glu.h"
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"
#include "circle.h"
#include "rectangle.h"
#include "allstructs.h"


const int WIDTH_WINDOW = 1000;
const int HEIGHT_WINDOW = 1000;
const int PANEL_BORD_PADDING = 60;
const char* WINDOW_NAME = "CAT-MAP";
const int MIN_HEIGHT_WINDOW = 700;
const int side_of_figure = 20;
const int STEP = 20;
int flag = 0;

int xf, yf, xs, ys;
int width_indicator = 0;
int height_indicator = 0;

// TODO: check code style for the name
typedef enum Drawing_state 
{
  DRAWING_TRIANGlE,
  DRAWING_RECT,
  ///....
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
/* initial coordinates of buttons: */
/* triangle */
const int X_FST_T = 30;
const int X_SND_T = 20;
const int X_TRD_T = 40;
const int Y_FST_T = 590;
const int Y_SCD_T = 570;
const int Y_TRD_T = 570;
/* line */
const int X_FST_L = 20;
const int X_SND_L = 40;
const int Y_FST_L = 510;
const int Y_SND_L = 530;


typedef enum Figure 
{
  RECTANGLE, TRIANGLE, LINE, CIRCLE
} Figure;


typedef struct Panel_border
{
  Rectangle rect;
} Panel_border;


Button* coordinates[10];

Panel_border* border = NULL;
Button* button_rect = NULL;
Button* button_triangle = NULL;
Button* button_line = NULL;
Button* button_circle = NULL;
Linked_list* linked_list = NULL;

Panel_border* createPanelBorder(int x, int y, int width)
{
  Panel_border* border = malloc(sizeof(Panel_border));
  border->rect.point.x = x;
  border->rect.point.y = y;
  border->rect.width = width;

  return border;
}

Button* createButtonTriangle(int x1, int y1, int x2, int y2, int x3,  int y3)
{
  Button* button_triangle = malloc(sizeof(Button));
  button_triangle->first_point.x = x1;
  button_triangle->first_point.y = y1;
  button_triangle->sec_point.x = x2;
  button_triangle->sec_point.y = y2;
  button_triangle->third_point.x = x3;
  button_triangle->third_point.y = y3;

  return button_triangle;
}

Button* createButtonLine(int x1, int y1, int x2, int y2)
{
  Button* button_line = malloc(sizeof(Button));
  button_line->point_line_first.x = x1;
  button_line->point_line_first.y = y1;
  button_line->point_line_sec.x = x2;
  button_line->point_line_sec.y= y2;

  return button_line;
}

void init(void)
{
  border = createPanelBorder(X_BORD, Y_BORD, WIDTH_BORD);

  button_rect = initRect();
  button_triangle = createButtonTriangle(X_FST_T, Y_FST_T, X_SND_T, Y_SCD_T, X_TRD_T, Y_TRD_T);
  button_line = createButtonLine(X_FST_L, Y_FST_L, X_SND_L, Y_SND_L);
  button_circle = initCircle();
  
  //coordinates[0] = button_rect;
  coordinates[1] = button_triangle;
  coordinates[2] = button_line;
  //coordinates[3] = button_circle;
  linked_list = createLinkedList();
}

void reshape(int width, int height)
{
  /* Minimum height is MIN_HEIGHT_WINDOW.
   * Window's size can not be smaller than this value. */
  if (height < MIN_HEIGHT_WINDOW) {
    glutReshapeWindow(width_indicator, MIN_HEIGHT_WINDOW);
  }
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  width_indicator = width;
  height_indicator = height;
}

void drawPanel(Panel_border* border)
{
  int x, y, width, height;
  x = border->rect.point.x;
  y = border->rect.point.y;
  width = border->rect.width;
  height = height_indicator;

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
  for (x = 0; x < width_indicator; x += STEP) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x, 0);
      glVertex2d(x, height_indicator);
    glEnd();
    glFlush();
  }
  /* horizontal lines */
  for (y = 0; y < height_indicator; y += STEP) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(0, y);
      glVertex2d(width_indicator, y);
    glEnd();
    glFlush();
  }
}

void drawTriangleButton(Button* button_triangle)
{
  int x1, x2, x3, y1, y2, y3;
  x1 = button_triangle->first_point.x;
  y1 = button_triangle->first_point.y;
  x2 = button_triangle->sec_point.x;
  y2 = button_triangle->sec_point.y;
  x3 = button_triangle->third_point.x;
  y3 = button_triangle->third_point.y;

  glColor3f(1.0, 0.0, 0.3);
  glBegin(GL_TRIANGLES);               
    glVertex2f(x1, y1);        
    glVertex2f(x2, y2);       
    glVertex2f(x3, y3);    
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  glLineWidth(4.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(x2, y2);               
    glVertex2f(x3, y3);         
    glVertex2f(x3, y3 + STEP);  
    glVertex2f(x2, y2 + STEP);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void drawLineButton(Button* button_line) 
{
  int x1, y1, x2, y2;
  x1 = button_line->point_line_first.x;
  y1 = button_line->point_line_first.y;
  x2 = button_line->point_line_sec.x;
  y2 = button_line->point_line_sec.y;
 
  glColor3f(0.0,0.4,0.2); 
  glLineWidth(3.0); 
  glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  glLineWidth(4.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);               
    glVertex2f(x1 + STEP, y1);         
    glVertex2f(x2, y2);  
    glVertex2f(x1, y1 + STEP);
  glEnd();
  glFlush();
  glutSwapBuffers();
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

void drawRectangle(int x, int y) 
{
  int width = 20;
  int height = 20;

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);              
    glVertex2f(x, y);               
    glVertex2f(x + width, y);         
    glVertex2f(x + width, y + height);  
    glVertex2f(x, y + height);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void drawCircle(int x, int y, int radius)
{
  int i;
  int triangleAmount = 20;
  double twicePi = 2 * M_PI;

  glColor3f(0.0, 0.4, 0.2);
  glBegin(GL_TRIANGLE_FAN);
    /* center of circle */
    glVertex2f(x, y); 
    for (i = 0; i <= triangleAmount; i++) { 
      glVertex2f(
      x + (radius * cos(i * twicePi / triangleAmount)), 
      y + (radius * sin(i * twicePi / triangleAmount)));
    }
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void drawLine(int x1, int y1, int x2, int y2) 
{
  glColor3f(0.0,0.4,0.2); 
  glPointSize(3.0);  
  glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void clickForLine(int button, int state, int x, int y)
{ 
  Node_coordinates* piece = NULL;
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    drawCircle(x, y, 5);
    addNode(linked_list, x, y);
    size_t number_of_nodes = count(linked_list);

    if (number_of_nodes > 1) {
      piece = getByIndex(linked_list, number_of_nodes - 2);
      drawLine(piece->x, piece->y, x, y);
    }
  }
}

/* check what button was pressed */
Figure checkCollision(int x, int y)
{
  Figure figure;
  if (y > button_rect->rect.point.y && y < (button_rect->rect.point.y + side_of_figure)) {
    figure = RECTANGLE;
  }
  
  if (y > button_triangle->sec_point.y && y < button_triangle->first_point.y) {
    figure = TRIANGLE;
  }

  if (y > button_line->point_line_first.y && y < button_line->point_line_sec.y) {
    figure = LINE;
  } else if(y > button_circle->point_circle.y - (side_of_figure / 2) && y < button_circle->point_circle.y + (side_of_figure / 2)) {
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
    flag = 1;
  } else if (figure == TRIANGLE) {
    flag = 2;
  } else if (figure == LINE) {
    flag = 3;
  } else if (figure == CIRCLE) {
    flag = 4;
  }
}

/* draw figure what was chosen from the buttons */
void mouse(int button, int state, int x, int y)
{
  int new_y = height_indicator - y;
  int a;
  a = (x > 60);
  printf(" XX - %d\n", x);
  printf("YY - %d\n", new_y);
  initFlag(x, new_y); 

  if (flag == 1 && a) {
    drawRectangle(x, new_y);
  } else if (flag == 4 && a) {
    drawCircle(x, new_y, 10);
  } else if (flag == 3 && a) {
    clickForLine(button, state, x, new_y);
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
  freeNodes(linked_list);
  free(linked_list);

  return 0;
}