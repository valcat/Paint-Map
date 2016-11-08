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
#include "circle.h"
#include "rectangle.h"
#include "line.h"
#include "triangle.h"
#include "graph.h"

double findLengthOfEdge(int point1_x, int point1_y, int point2_x, int point2_y) 
{
	double length;
	length = sqrt((pow((point1_x - point2_x), 2) + pow((point1_y - point2_y), 2));
	return length;
}