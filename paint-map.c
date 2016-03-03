#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdbool.h>

typedef struct Panel_tools
{
  //coordinates of panel's boorder
  int x_border;
  int y_border;
  int width_border;
  int height_border;
  //tools for drawing
  int x_rect;
  int y_rect;
  int width_rect;
  int height_rect;
} Panel_tools;

Panel_tools* border = NULL;
Panel_tools* tool_rect = NULL;

Panel_tools* create_panel_border(int x, int y, int width, int height)
{
  Panel_tools* border = malloc(sizeof(Panel_tools));
  border->x_border = x;
  border->y_border = y;
  border->width_border = width;
  border->height_border = height;

  return border;
}

Panel_tools* create_tool_rect(int x, int y, int width, int height)
{
  Panel_tools* tool_rect = malloc(sizeof(Panel_tools));
  tool_rect->x_rect = x;
  tool_rect->y_rect = y;
  tool_rect->width_rect = width;
  tool_rect->height_rect = height;

  return tool_rect;
}

void init(void)
{
  Panel_tools* border = create_panel_border(0, 0, 60, 800);
  Panel_tools* tool_rect = create_tool_rect(20, 740, 20, 20);
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

void draw_panel(Panel_tools* border)
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

void draw_rectangle(Panel_tools *tool_rect) 
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

void draw_greed(void)
{
  double x = 60;
  double y = 0;
  int i = 0;
  int j = 0;
  int width = 800;
  int height = 800;
  double step = 20;
  double num_lines = width / step;

  //vertical lines
  for (i = 0; i < num_lines; i++) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(x, 0);
      glVertex2d(x, height);
    glEnd();
    x = x + step;
    glFlush();
  }
  //horizontal lines
  for (i = 0; i < num_lines; i++) {
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(1);
    glBegin(GL_LINES);
      glVertex2d(60, y);
      glVertex2d(width, y);
    glEnd();
    y = y + step;
    glFlush();
  }
}

void draw_rectangle2(int x, int y) 
{
  double width = 20;
  double height = 20;

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

void draw_rectangle_frame(void) 
{
  double x = 20;
  double y = 740;
  double width = 20;
  double height = 20;

  glColor3f(0.0, 0.0, 0.0);
  glBegin(GL_LINES);
    glVertex2d(20, 760);             
    glVertex2d(40, 760); 
    glVertex2d(40, 760); 
    glVertex2d(40, 740);              
    glVertex2d(40, 740);             
    glVertex2d(20, 740);
    glVertex2d(20, 740);
    glVertex2d(20, 760);                   
  glEnd();  
  glFlush();
  glutSwapBuffers();
}

void draw_triangle(void)
{
  glBegin(GL_TRIANGLES);          
    glColor3f(0.0f,1.0f,0.0f);      
    glVertex2f( 30.0f, 680.0f);    
    glColor3f(0.0f,0.0f,1.0f);      
    glVertex2f(20.0f, 660.0f);    
    glColor3f(1.0f,0.0f,0.0f);      
    glVertex2f( 40.0f, 660.0f);    
  glEnd();
  glFlush();
  glutSwapBuffers();
}

void draw(void)
{
  Panel_tools* border = create_panel_border(0, 0, 60, 800);
  Panel_tools* tool_rect = create_tool_rect(20, 740, 20, 20);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  draw_panel(border);
  draw_rectangle(tool_rect);
  draw_greed();
  draw_triangle();
}

void mouse(int button, int state, int x, int y)
{
  int new_y = 800 - y;
  printf("x - %d\n", x);
  printf("y - %d\n", new_y);
  if ((x >= 20) && (x <= 40) && (new_y >= 740) && (new_y <= 760)) {
    printf("hoh\n");
    draw_rectangle_frame();
  }
  if ((x > 60)) {
    draw_rectangle2(x, new_y);
  }
}

int main(int argc, char *argv[])
{
  //init();
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(800, 800);
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