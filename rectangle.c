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

const int X_RECT = 20;
const int Y_RECT = 630;
const int WIDTH_RECT = 20;
const int HEIGHT_RECT = 20;

Button* createButtonRect(int x, int y, int width, int height)
{
  Button* button_rect = malloc(sizeof(Button));
  button_rect->rect.point.x = x;
  button_rect->rect.point.y = y;
  button_rect->rect.width = width;
  button_rect->rect.height = height;

  return button_rect;
}

Button* initRect()
{
	Button* button_rect = NULL;
	button_rect = createButtonRect(X_RECT, Y_RECT, WIDTH_RECT, HEIGHT_RECT);
	return button_rect;
}

void drawRectangleButton(Button* button_rect) 
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