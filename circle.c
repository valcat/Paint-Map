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
#include "allstructs.h"

/* circle */
const int X_CRL = 30;
const int Y_CRL = 460;
const int RADS = 10;
const int NUM_SGMTS = 360;
const int SEGMENT = 20;

MapState stateCircle;

Button* createButtonCircle(int x, int y, int radius, int num_segments)
{
  stateCircle.button_circle = malloc(sizeof(Button));
  stateCircle.button_circle->point_circle.x = x;
  stateCircle.button_circle->point_circle.y = y;
  stateCircle.button_circle->radius = radius;
  stateCircle.button_circle->num_segments = num_segments;

  return stateCircle.button_circle;
}

Button* initCircle()
{
	stateCircle.button_circle = createButtonCircle(X_CRL, Y_CRL, RADS, NUM_SGMTS);
	return stateCircle.button_circle;
}

void drawCircleButton(Button* button_circle)
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
}

void drawCircle(int x, int y, int radius)
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
}

void shinePoint(int x, int y, int radius)
{
  int i;
  int triangleAmount = 20;
  double twicePi = 2 * M_PI;

  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_TRIANGLE_FAN);
    /* center of circle */
    glVertex2f(x, y); 
    for (i = 0; i <= triangleAmount; i++) { 
      glVertex2f(
      x + (radius * cos(i * twicePi / triangleAmount)), 
      y + (radius * sin(i * twicePi / triangleAmount)));
    }
  glEnd();
}

