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
#include "rectangle.h"
#include "triangle.h"

const int X_FST_T = 30;
const int X_SND_T = 20;
const int X_TRD_T = 40;
const int Y_FST_T = 590;
const int Y_SCD_T = 570;
const int Y_TRD_T = 570;
const int STEP_T = 20;

MapState stateTriangle;

Button* createButtonTriangle(int x1, int y1, int x2, int y2, int x3,  int y3)
{
  stateTriangle.button_triangle = malloc(sizeof(Button));
  stateTriangle.button_triangle->first_point.x = x1;
  stateTriangle.button_triangle->first_point.y = y1;
  stateTriangle.button_triangle->sec_point.x = x2;
  stateTriangle.button_triangle->sec_point.y = y2;
  stateTriangle.button_triangle->third_point.x = x3;
  stateTriangle.button_triangle->third_point.y = y3;

  return stateTriangle.button_triangle;
}

Button* initTriangle()
{
	stateTriangle.button_triangle = createButtonTriangle(X_FST_T, Y_FST_T, X_SND_T, Y_SCD_T, X_TRD_T, Y_TRD_T);
	return stateTriangle.button_triangle;
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
    glVertex2f(x3, y3 + STEP_T);  
    glVertex2f(x2, y2 + STEP_T);
  glEnd();
}