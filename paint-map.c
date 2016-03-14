#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdbool.h>

const int HEIGHT_WINDOW = 800;
const int WIDTH_WINDOW = 800;
const int PANEL_BORD_PADDING = 60;
const char* WINDOW_NAME = "CAT-MAP";
int flag = 0;

typedef enum Figure 
{
  RECTANGLE, TRIANGLE, LINE
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

typedef struct Geed
{
  int x_vert;
  int y_vert;
  int x_hor;
  int y_hor;
  int step;
} Greed;

typedef struct Button
{
  Rectangle rect;
  //triangle
  int x_tr_1st;
  int y_tr_1st;
  int x_tr_2d;
  int y_tr_2d;
  int x_tr_3d;
  int y_tr_3d;
  //line
  int x_line_1st;
  int y_line_1st;
  int x_line_2d;
  int y_line_2d;
  Figure figure;
} Button;

Panel_border* border = NULL;
Button* button_rect = NULL;
Button* button_triangle = NULL;
Button* button_line = NULL;
Greed* greed = NULL;

Panel_border* create_panel_border(int x, int y, int width, int height)
{
  Panel_border* border = malloc(sizeof(Panel_border));
  border->rect.point.x = x;
  border->rect.point.y = y;
  border->rect.width= width;
  border->rect.height= height;

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
  button_triangle->x_tr_1st = x1;
  button_triangle->y_tr_1st = y1;
  button_triangle->x_tr_2d = x2;
  button_triangle->y_tr_2d = y2;
  button_triangle->x_tr_3d = x3;
  button_triangle->y_tr_3d = y3;

  return button_triangle;
}

Button* create_button_line(int x1, int y1, int x2, int y2)
{
  Button* button_line = malloc(sizeof(Button));
  button_line->x_line_1st = x1;
  button_line->y_line_1st = y1;
  button_line->x_line_2d = x2;
  button_line->y_line_2d = y2;

  return button_line;
}

Greed* create_greed(int x_hor, int y_hor, int x_vert, int y_vert, int step)
{
  Greed* greed = malloc(sizeof(Greed));
  greed->x_hor = x_hor;
  greed->y_hor = y_hor;
  greed->x_vert = x_vert;
  greed->y_vert = y_vert;
  greed->step = step;

  return greed;
}

void init(void)
{
  border = create_panel_border(0, 0, 60, 800);
  button_rect = create_button_rect(20, 740, 20, 20);
  button_triangle = create_button_triangle(30, 680, 20, 660, 40, 660);
  button_line = create_button_line(20, 600, 40, 620);
  greed = create_greed(60, 0, 60, 0, 20);
}

void reshape(int width, int height)
{
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, width, 0.0, height, 0.0, 1.0);
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

void draw_greed(Greed* greed)
{
  int x1, y1, x2, y2, step;
  int i = 0;
  x1 = greed->x_hor;
  y1 = greed->y_hor;
  x2 = greed->x_hor;
  y2 = greed->y_hor;
  step = greed->step;

  int num_lines = WIDTH_WINDOW / step;

  //vertical lines
  for (i = 0; i < num_lines; i++) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x1, y1);
      glVertex2d(x1, HEIGHT_WINDOW);
    glEnd();
    x1 = x1 + step;
    glFlush();
  }
  //horizontal lines
  for (i = 0; i < num_lines; i++) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x2, y2);
      glVertex2d(WIDTH_WINDOW, y2);
    glEnd();
    y2 = y2 + step;
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

  glColor3f(0.0, 0.0, 0.0);
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
  int step = 20;
  x1 = button_triangle->x_tr_1st;
  y1 = button_triangle->y_tr_1st;
  x2 = button_triangle->x_tr_2d;
  y2 = button_triangle->y_tr_2d;
  x3 = button_triangle->x_tr_3d;
  y3 = button_triangle->y_tr_3d;

  glColor3f(1.0, 0.0, 0.3);
  glBegin(GL_TRIANGLES);               
    glVertex2f(x1, y1);        
    glVertex2f(x2, y2);       
    glVertex2f(x3, y3);    
  glEnd();

  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(x2, y2);               
    glVertex2f(x3, y3);         
    glVertex2f(x3, y3 + step);  
    glVertex2f(x2, y2 + step);
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void draw_line_button(Button* button_line) 
{
  int x1, y1, x2, y2;
  int step = 20;
  x1 = button_line->x_line_1st;
  y1 = button_line->y_line_1st;
  x2 = button_line->x_line_2d;
  y2 = button_line->y_line_2d;
 
  glColor3f(0.0,0.4,0.2); 
  glPointSize(3.0);  
  glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  glEnd();

  glColor3f(0.0, 0.0, 0.0);
  glPointSize(8.0);
  glBegin(GL_LINE_LOOP);
    glVertex2f(x1, y1);               
    glVertex2f(x1 + step, y1);         
    glVertex2f(x2, y2);  
    glVertex2f(x1, y1 + step);
  glEnd();
  glFlush();
  glutSwapBuffers();
} 

void draw_buttons(void)
{
  draw_rectangle_button(button_rect);
  draw_triangle_button(button_triangle);
  draw_line_button(button_line);
}

void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  //draw working window and panel with set of tools
  draw_greed(greed);
  draw_panel(border);
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

void mouse(int button, int state, int x, int y)
{
  int new_y = HEIGHT_WINDOW - y;
  printf("x - %d\n", x);
  printf("y - %d\n", new_y);

  if ((x >= 20) && (x <= 40) && (new_y >= 740) && (new_y <= 760)) {
    flag = 1;
  }
  switch (flag) {
    case 1:
      if (x > PANEL_BORD_PADDING) {
        draw_rectangle2(x, new_y);
        //printf("Yes\n");
      }
      break;
    case 2:
      draw_rectangle2(x, new_y);
      break;
  }  
}

int main(int argc, char *argv[])
{
  init();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(HEIGHT_WINDOW, WIDTH_WINDOW);
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
  free(greed);

  return 0;
}