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

MapState stateRect;

Button* createButtonRect(int x, int y, int width, int height)
{
  stateRect.button_rect = malloc(sizeof(Button));
  stateRect.button_rect->rect.point.x = x;
  stateRect.button_rect->rect.point.y = y;
  stateRect.button_rect->rect.width = width;
  stateRect.button_rect->rect.height = height;

  return stateRect.button_rect;
}

Button* initRect()
{
	stateRect.button_rect = createButtonRect(X_RECT, Y_RECT, WIDTH_RECT, HEIGHT_RECT);
	return stateRect.button_rect;
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
}