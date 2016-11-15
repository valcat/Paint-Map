#ifndef EDGE_H
#define EDGE_H
#include "allstructs.h"
#include "linked_list.h"
#include "circle.h"

Edge* createEdge(Point* point_1st, Point* point_2nd);
void saveEdge(Linked_list* linked_list, Point* point1, Point* point2);
void drawEdges(Linked_list* linked_list);
void drawEdgeVertices(Linked_list* linked_list, int radius);

#endif