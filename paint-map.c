#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/glu.h"
#include <stdbool.h>
#include <math.h>

const int WIDTH_WINDOW = 1000;
const int HEIGHT_WINDOW = 800;
const int PANEL_BORD_PADDING = 60;
const char* WINDOW_NAME = "CAT-MAP";
const int STEP = 20;
const int side_of_figure = 20;
int flag = 0;

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
  //triangle
  Point first_point;
  Point sec_point;
  Point third_point;
  //line
  Point point_line_first;
  Point point_line_sec;
  //circle
  Point point_circle;
  int radius;
  int num_segments;
} Button;

Button* coordinates[10];

Panel_border* border = NULL;
Button* button_rect = NULL;
Button* button_triangle = NULL;
Button* button_line = NULL;
Button* button_circle = NULL;

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
  border = create_panel_border(0, 0, 60, HEIGHT_WINDOW);

  button_rect = create_button_rect(20, 720, 20, 20);
  button_triangle = create_button_triangle(30, 680, 20, 660, 40, 660);
  button_line = create_button_line(20, 600, 40, 620);
  button_circle = create_button_circle(30, 550, 10, 360);
  coordinates[0] = button_rect;
  coordinates[1] = button_triangle;
  coordinates[2] = button_line;
  coordinates[3] = button_circle;
}

void reshape(int width, int height)
{
  if (width < 1000 || height < 800) {
    glutReshapeWindow( 1000, 800);
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, width, height);
  gluOrtho2D(0, WIDTH_WINDOW, 0, HEIGHT_WINDOW);
  glMatrixMode (GL_MODELVIEW);
  glLoadIdentity();
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

  //vertical lines
  for (x = 0; x < WIDTH_WINDOW; x += STEP) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x, 0);
      glVertex2d(x, HEIGHT_WINDOW);
    glEnd();
    glFlush();
  }
  //horizontal lines
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

  glColor3f(0.0, 1.0, 1.0);
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

void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  //draw working window and panel with set of tools
  draw_grid();
  draw_panel(border);
  glColor3f(0, 0, 0);
  drawBitmapText("Tools", 2, 770);
  draw_buttons();
}

//to delete
void draw_rectangle2(int x, int y) 
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

//to delete
void draw_line2(int x1, int y1) 
{
  glColor3f(0.0,0.4,0.2); 
  glPointSize(3.0);  

  glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x1, y1);
  glEnd();
  glFlush();
  glutSwapBuffers();
} 

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

void mouse(int button, int state, int x, int y)
{
  
  int new_y = HEIGHT_WINDOW - y;
  int beginig_x = 20;
  int end_x = 40;

   if (x > beginig_x && x < end_x) {
    check_button(x, new_y);   
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
  glutReshapeFunc(reshape);
  glutDisplayFunc(draw);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glutMouseFunc(mouse);
  glutMainLoop();
  free(border);
  free(button_rect);
  free(button_triangle);
  free(button_line);

  return 0;
}