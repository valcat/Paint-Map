#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdbool.h>

int height_window = 800;
int width_window = 800;
int flag = 0;

typedef struct Panel_border
{
  //coordinates of panel's border
  int x_border;
  int y_border;
  int width_border;
  int height_border;
  
} Panel_border;

typedef struct Button
{
  //tools for drawing
  //rectangle
  int x_rect;
  int y_rect;
  int width_rect;
  int height_rect; 
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
  
} Button;


Panel_border* border = NULL;
Button* tool_rect = NULL;
Button* tool_triangle = NULL;
Button* tool_line = NULL;

Panel_border* create_panel_border(int x, int y, int width, int height)
{
  Panel_border* border = malloc(sizeof(Panel_border));
  border->x_border = x;
  border->y_border = y;
  border->width_border = width;
  border->height_border = height;

  return border;
}

Button* create_tool_rect(int x, int y, int width, int height)
{
  Button* tool_rect = malloc(sizeof(Button));
  tool_rect->x_rect = x;
  tool_rect->y_rect = y;
  tool_rect->width_rect = width;
  tool_rect->height_rect = height;

  return tool_rect;
}

Button* create_tool_triangle(int x1, int y1, int x2, int y2, int x3,  int y3)
{
  Button* tool_triangle = malloc(sizeof(Button));
  tool_triangle->x_tr_1st = x1;
  tool_triangle->y_tr_1st = y1;
  tool_triangle->x_tr_2d = x2;
  tool_triangle->y_tr_2d = y2;
  tool_triangle->x_tr_3d = x3;
  tool_triangle->y_tr_3d = y3;

  return tool_triangle;
}

Button* create_tool_line(int x1, int y1, int x2, int y2)
{
  Button* tool_line = malloc(sizeof(Button));
  tool_line->x_line_1st = x1;
  tool_line->y_line_1st = y1;
  tool_line->x_line_2d = x2;
  tool_line->y_line_2d = y2;

  return tool_line;
}

void init(void)
{
  border = create_panel_border(0, 0, 60, 800);
  tool_rect = create_tool_rect(20, 740, 20, 20);
  tool_triangle = create_tool_triangle(30, 680, 20, 660, 40, 660);
  tool_line = create_tool_line(20, 600, 40, 620);
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
  x = border->x_border;
  y = border->y_border;
  width = border->width_border;
  height = border->height_border;

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

void draw_greed(void)
{
  //begining of the greed
  int x_vert = 60;
  int y_vert = 0;
  int x_hor = 60;
  int y_hor = 0;

  int i = 0;
  int step = 20;
  int num_lines = width_window / step;

  //vertical lines
  for (i = 0; i < num_lines; i++) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x_vert, y_vert);
      glVertex2d(x_vert, height_window);
    glEnd();
    x_vert = x_vert + step;
    glFlush();
  }
  //horizontal lines
  for (i = 0; i < num_lines; i++) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x_hor, y_hor);
      glVertex2d(width_window, y_hor);
    glEnd();
    y_hor = y_hor + step;
    glFlush();
  }
}

void draw_rectangle(Button *tool_rect) 
{
  int x, y, width, height;
  x = tool_rect->x_rect;
  y = tool_rect->y_rect;
  width = tool_rect->width_rect;
  height = tool_rect->height_rect;

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

void draw_triangle(Button* tool_triangle)
{
  int x1, x2, x3, y1, y2, y3;
  x1 = tool_triangle->x_tr_1st;
  y1 = tool_triangle->y_tr_1st;
  x2 = tool_triangle->x_tr_2d;
  y2 = tool_triangle->y_tr_2d;
  x3 = tool_triangle->x_tr_3d;
  y3 = tool_triangle->y_tr_3d;

  glColor3f(1.0, 0.0, 0.3);
  glBegin(GL_TRIANGLES);               
    glVertex2f(x1, y1);        
    glVertex2f(x2, y2);       
    glVertex2f(x3, y3);    
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void draw_line(Button* tool_line) 
{
  int x1, y1, x2, y2;
  x1 = tool_line->x_line_1st;
  y1 = tool_line->y_line_1st;
  x2 = tool_line->x_line_2d;
  y2 = tool_line->y_line_2d;
 
  glColor3f(0.0,0.4,0.2); 
  glPointSize(3.0);  

  glBegin(GL_LINES);
    glVertex2d(x1, y1);
    glVertex2d(x2, y2);
  glEnd();
  glFlush();
  glutSwapBuffers();
} 

void draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  //draw working window and panel with set of tools
  draw_greed();
  draw_panel(border);
  draw_rectangle(tool_rect);
  draw_triangle(tool_triangle);
  draw_line(tool_line);
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
  int new_y = height_window - y;
  int panel_bord_end = 60;
  printf("x - %d\n", x);
  printf("y - %d\n", new_y);

  if ((x >= 20) && (x <= 40) && (new_y >= 740) && (new_y <= 760)) {
    flag = 1;
  }
  switch (flag) {
    case 1:
      if (x > panel_bord_end) {
        //draw_rectangle2(x, new_y);
        draw_line2(x, new_y);
        printf("FO\n");
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
  glutInitWindowSize(height_window, width_window);
  glutInitWindowPosition(0, 0);
  glutCreateWindow("Cat-pensil");
  glutReshapeFunc(reshape);
  glutDisplayFunc(draw);
  glClearColor(1.0, 1.0, 1.0, 1.0);
  glutMouseFunc(mouse);
  glutMainLoop();
  free(border);
  free(tool_rect);

  return 0;
}