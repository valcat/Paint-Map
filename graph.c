#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/glu.h"
#include <stdbool.h>
#include <math.h>
#include "allstructs.h"
#include "linked_list.h"
#include "graph.h"


Edge* createEdge(Point* point_1st, Point* point_2nd)
{
	Edge* edge = malloc(sizeof(Edge));
	edge->point1 = point_1st;
	edge->point2 = point_2nd;
	return edge;
}
