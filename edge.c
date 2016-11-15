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
#include "edge.h"
#include "line.h"
#include "circle.h"


Edge* createEdge(Point* point_1st, Point* point_2nd)
{
	Edge* edge = malloc(sizeof(Edge));
	edge->point1 = point_1st;
	edge->point2 = point_2nd;
	return edge;
}

void saveEdge(Linked_list* linked_list, Point* point1, Point* point2)
{
  Edge* edge;
  edge = createEdge(point1, point2);
  addNode(linked_list, edge);
}

void drawEdges(Linked_list* linked_list)
{
  Node* indexNode = linked_list->head;
  Edge* edge;

  while (indexNode) {  
    edge = indexNode->element; 
    drawingLine(edge->point1->x, edge->point1->y, edge->point2->x, edge->point2->y);
    indexNode = indexNode->next; 
  }
}

void drawEdgeVertices(Linked_list* linked_list, int radius)
{
  size_t number_of_nodes = count(linked_list);
  size_t count = 0;
  Node* indexNode = linked_list->head;
  Point* point1;
  Point* point2;

  if (number_of_nodes > 1) {
    while (indexNode) {   
      point1 = indexNode->element;
      
      if (count < number_of_nodes - 1) {
        point2 = indexNode->next->element;
      }
      drawCircle(point1->x, point1->y, radius);
      count++;  
      indexNode = indexNode->next; 
    }
  }   
}