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

/* circle */
const int X_CRL = 30;
const int Y_CRL = 460;
const int RADS = 10;
const int NUM_SGMTS = 360;
const int SEGMENT = 20;


Button_c* createButtonCircle(int x, int y, int radius, int num_segments)
{
  Button_c* button_circle = malloc(sizeof(Button_c));
  button_circle->point_circle.x = x;
  button_circle->point_circle.y = y;
  button_circle->radius = radius;
  button_circle->num_segments = num_segments;

  return button_circle;
}

Button_c* initCircle()
{
	Button_c* button_circle = NULL;
	button_circle = createButtonCircle(X_CRL, Y_CRL, RADS, NUM_SGMTS);
	return button_circle;
}

void drawCircleButton(Button_c* button_circle)
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
  half_step = SEGMENT / 2;

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

