#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/glu.h"
#include <stdbool.h>
#include <math.h>

const int WIDTH_WINDOW = 1000;
const int HEIGHT_WINDOW =800;
const int PANEL_BORD_PADDING = 60;
const char* WINDOW_NAME = "CAT-MAP";
const int STEP = 20;
const int side_of_figure = 20;
int flag = 0;
int indicator = 0;
int xf, yf, xs, ys;

/* initial coordinates of border */
const int X_BORD = 0;
const int Y_BORD = 0;
const int WIDTH_BORD = 60;
/* initial coordinates of buttons: */
/* rectangle */
const int X_RECT = 20;
const int Y_RECT = 720;
const int WIDTH_RECT = 20;
const int HEIGHT_RECT = 20;
/* triangle */
const int X_FST_T = 30;
const int X_SND_T = 20;
const int X_TRD_T = 40;
const int Y_FST_T = 680;
const int Y_SCD_T = 660;
const int Y_TRD_T = 660;
/* line */
const int X_FST_L = 20;
const int X_SND_L = 40;
const int Y_FST_L = 600;
const int Y_SND_L = 620;
/* circle */
const int X_CRL = 30;
const int Y_CRL = 550;
const int RADS = 10;
const int NUM_SGMTS = 360;


typedef enum Figure 
{
  RECTANGLE, TRIANGLE, LINE, CIRCLE
} Figure;

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

typedef struct Node_coordinates
{
  int x, y;
  struct Node_coordinates *next;
} Node_coordinates;

typedef struct Linked_list
{
  Node_coordinates *head;
} Linked_list;

Button* coordinates[10];

Panel_border* border = NULL;
Button* button_rect = NULL;
Button* button_triangle = NULL;
Button* button_line = NULL;
Button* button_circle = NULL;
Linked_list* linked_list = NULL;
Node_coordinates *store_nodes = NULL;

Linked_list* create_linked_list();

Panel_border* create_panel_border(int x, int y, int width, int height)
{
  Panel_border* border = malloc(sizeof(Panel_border));
  border->rect.point.x = x;
  border->rect.point.y = y;
  border->rect.width = width;
  border->rect.height = height;

  return border;
}

Button* create_button_rect(int x, int y, int width, int height)
{
  Button* button_rect = malloc(sizeof(Button));
  button_rect->rect.point.x = x;
  button_rect->rect.point.y = y;
  button_rect->rect.width = width;
  button_rect->rect.height = height;

  return button_rect;
}

Button* create_button_triangle(int x1, int y1, int x2, int y2, int x3,  int y3)
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

Button* create_button_line(int x1, int y1, int x2, int y2)
{
  Button* button_line = malloc(sizeof(Button));
  button_line->point_line_first.x = x1;
  button_line->point_line_first.y = y1;
  button_line->point_line_sec.x = x2;
  button_line->point_line_sec.y= y2;

  return button_line;
}

Button* create_button_circle(int x, int y, int radius, int num_segments)
{
  Button* button_circle = malloc(sizeof(Button));
  button_circle->point_circle.x = x;
  button_circle->point_circle.y = y;
  button_circle->radius = radius;
  button_circle->num_segments = num_segments;

  return button_circle;
}

void init(void)
{
  border = create_panel_border(X_BORD, Y_BORD, WIDTH_BORD, HEIGHT_WINDOW);

  button_rect = create_button_rect(X_RECT, Y_RECT, WIDTH_RECT, HEIGHT_RECT);
  button_triangle = create_button_triangle(X_FST_T, Y_FST_T, X_SND_T, Y_SCD_T, X_TRD_T, Y_TRD_T);
  button_line = create_button_line(X_FST_L, Y_FST_L, X_SND_L, Y_SND_L);
  button_circle = create_button_circle(X_CRL, Y_CRL, RADS, NUM_SGMTS);
  
  coordinates[0] = button_rect;
  coordinates[1] = button_triangle;
  coordinates[2] = button_line;
  coordinates[3] = button_circle;
  linked_list = create_linked_list();
}

void reshape(int width, int height)
{
  /* Minimum width of the window is WIDTH_WINDOW, minimum height is HEIGHT_WINDOW.
   * Window's size can not be smaller than these values. */
  if (width < WIDTH_WINDOW || height < HEIGHT_WINDOW) {
    glutReshapeWindow(WIDTH_WINDOW, HEIGHT_WINDOW);
  }
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width, 0, height);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}

void draw_panel(Panel_border* border)
{
  int x, y, width, height;
  x = border->rect.point.x;
  y = border->rect.point.y;
  width = border->rect.width;
  height = border->rect.height;

  glColor3f(0.9, 0.9, 0.9);
  glBegin(GL_QUADS);              
    glVertex2f(x, y);               
    glVertex2f(x + width, y);         
    glVertex2f(x + width, y + height);  
    glVertex2f(x, y + height);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void draw_grid()
{
  int x, y;

  /* vertical lines */
  for (x = 0; x < WIDTH_WINDOW; x += STEP) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x, 0);
      glVertex2d(x, HEIGHT_WINDOW);
    glEnd();
    glFlush();
  }
  /* horizontal lines */
  for (y = 0; y < HEIGHT_WINDOW; y += STEP) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(0, y);
      glVertex2d(WIDTH_WINDOW, y);
    glEnd();
    glFlush();
  }
}

void draw_rectangle_button(Button *button_rect) 
{
  int x, y, width, height;
  x = button_rect->rect.point.x;
  y = button_rect->rect.point.y;
  width = button_rect->rect.width;
  height = button_rect->rect.height;
 
  glBegin(GL_QUADS); 
    glColor3f(0.0, 1.0, 0.0);           
    glVertex2f(x, y);               
    glVertex2f(x + width, y);         
    glVertex2f(x + width, y + height);  
    glVertex2f(x, y + height);
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  glLineWidth(4.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);               
    glVertex2f(x + width, y);         
    glVertex2f(x + width, y + height);  
    glVertex2f(x, y + height);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void draw_triangle_button(Button* button_triangle)
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

void draw_line_button(Button* button_line) 
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

void draw_circle_button(Button* button_circle)
{
  int i, cx, cy, num_segments, r, half_step;
  double theta, c, s, x;
  double t = 0.0;
  double y = 0;
  int dif = 2;
  cx = button_circle->point_circle.x;
  cy = button_circle->point_circle.y;
  num_segments = button_circle->num_segments;
  r = button_circle->radius;

  theta = 2 * M_PI / num_segments;
  c = cos(theta);
  s = sin(theta);
  x = r;
  half_step = STEP / 2;

  glColor3f(0.0, 0.4, 0.2);
  glBegin(GL_POLYGON);
  for (i = 0; i < num_segments; i++)
  {
    glVertex2f(x + cx, y + cy);
    t = x;
    x = c * x - s * y;
    y = s * t + c * y;
  } 
  glEnd();

  glColor3f(1.0, 1.0, 1.0);
  glLineWidth(4.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(cx - half_step - dif, cy - half_step - dif);               
    glVertex2f(cx + half_step + dif, cy - half_step - dif);         
    glVertex2f(cx + half_step + dif, cy + half_step + dif);  
    glVertex2f(cx - half_step - dif, cy + half_step + dif);
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

void draw_buttons(void)
{
  draw_rectangle_button(button_rect);
  draw_triangle_button(button_triangle);
  draw_line_button(button_line);
  draw_circle_button(button_circle);
}

/* function that draws window with all stuff */
void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  /* draw working window and panel with set of tools */
  draw_grid();
  draw_panel(border);
  glColor3f(0, 0, 0);
  drawBitmapText("Tools", 2, 770);
  draw_buttons();
  glFlush();
}

void draw_rectangle(int x, int y) 
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

void draw_circle(int x, int y, int radius)
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

void draw_line(int x1, int y1, int x2, int y2) 
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

void add_node(Linked_list *linked_list, int x, int y)
{
 
  if (linked_list->head) {
    Node_coordinates *IndexNode = linked_list->head;

    while (IndexNode->next) {
      IndexNode = IndexNode->next;
    }
    store_nodes = malloc(sizeof(Node_coordinates));
    store_nodes->x = x; 
    store_nodes->y = y;
    store_nodes->next = NULL;
    IndexNode->next = store_nodes;

  } else {
    store_nodes = malloc(sizeof(Node_coordinates));
    store_nodes->x = x;
    store_nodes->y = y;
    store_nodes->next = NULL;
    linked_list->head = store_nodes;
  }

}

Linked_list* create_linked_list() 
{
  Linked_list *list = malloc(sizeof(Linked_list));
  
  return list;
}

void click_for_line(int button, int state, int x, int y)
{ 
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    switch(indicator)
    {
      case 0:
        xf = x;
        yf = y;
        indicator = 1;
        draw_circle(xf, yf, 5);
        add_node(linked_list, xf, yf);
        /* check coordinates of the first point */
        printf("y - %d\n", store_nodes->y);
        printf("x - %d\n", store_nodes->x);
        break;
      case 1:
        xs = x;
        ys = y;
        draw_circle(xs, ys, 5);
        draw_line(xf, yf, xs, ys);
        indicator = 0;
        add_node(linked_list, xs, ys);
        /* check coordinates of the second point */
        printf("y2 - %d\n", store_nodes->y);
        printf("x2 - %d\n", store_nodes->x);
        break;
    }
  }
}

/* check what button was pressed */
Figure check_button(int x, int y)
{
  Figure figure;
  if (y > button_rect->rect.point.y && y < (button_rect->rect.point.y + side_of_figure)) {
      figure = RECTANGLE;
    } if (y > button_triangle->sec_point.y && y < button_triangle->first_point.y) {
      figure = TRIANGLE;
    } if (y > button_line->point_line_first.y && y < button_line->point_line_sec.y) {
      figure = LINE;
    } else if(y > button_circle->point_circle.y - (side_of_figure / 2) && y < button_circle->point_circle.y + (side_of_figure / 2)) {
      figure = CIRCLE;
    }

  return figure;
}

void init_flag(int x, int y) 
{
  int beginig_x = 20;
  int end_x = 40;
  Figure figure;

  if (x > beginig_x && x < end_x) {
    figure = check_button(x, y);   
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
  int new_y = HEIGHT_WINDOW - y;
  int a;
  a = (x > 60);
  printf(" XX - %d\n", x);
  init_flag(x, new_y); 

  if (flag == 1 && a) {
    draw_rectangle(x, new_y);
  } else if (flag == 4 && a) {
    draw_circle(x, new_y, 10);
  } else if (flag == 3 && a) {
    click_for_line(button, state, x, new_y);
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

  return 0;
}