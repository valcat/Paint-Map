#ifndef EDGE_H
#define EDGE_H
#include "allstructs.h"
#include "linked_list.h"
#include "circle.h"

Edge* saveEdge(Point* point_1st, Point* point_2nd);
//void saveEdge(Linked_list* linked_list, Point* point1, Point* point2);
void drawEdges(Linked_list* linked_list);
void drawEdgeVertices(Linked_list* linked_list, int radius);
double findLengthOfEdge(int point1_x, int point1_y, int point2_x, int point2_y);
void printLengthOfEdge(Linked_list* linked_list);


#endif