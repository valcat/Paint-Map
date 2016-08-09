#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/glu.h"
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"
#include "rectangle.h"
#include "allstructs.h"
#include "line.h"

const int X_FST_L = 20;
const int X_SND_L = 40;
const int Y_FST_L = 510;
const int Y_SND_L = 530;
const int STEP_L = 20;


Button* createButtonLine(int x1, int y1, int x2, int y2)
{
  Button* button_line = malloc(sizeof(Button));
  button_line->point_line_first.x = x1;
  button_line->point_line_first.y = y1;
  button_line->point_line_sec.x = x2;
  button_line->point_line_sec.y= y2;

  return button_line;
}

Button* initLine()
{
	Button* button_line = NULL;
	button_line = createButtonLine(X_FST_L, Y_FST_L, X_SND_L, Y_SND_L);
	return button_line;
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
    glVertex2f(x1 + STEP_L, y1);         
    glVertex2f(x2, y2);  
    glVertex2f(x1, y1 + STEP_L);
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