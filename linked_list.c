#include <stdio.h>
#include <stdlib.h>
#include <GL/glx.h>    
#include <GL/gl.h>
#include <GL/glut.h>
#include "GL/glu.h"
#include <stdbool.h>
#include <math.h>
#include "linked_list.h"

Linked_list* createLinkedList() 
{
  Linked_list *list = malloc(sizeof(Linked_list));
  
  return list;
}

void addNode(Linked_list *linked_list, int x, int y)
{
  Node_coordinates *piece = NULL;

  if (linked_list->head) {
    Node_coordinates *IndexNode = linked_list->head;

    while (IndexNode->next) {
      IndexNode = IndexNode->next;
    }
    piece = malloc(sizeof(Node_coordinates));
    piece->x = x; 
    piece->y = y;
    piece->next = NULL;
    IndexNode->next = piece;

  } else {
    piece = malloc(sizeof(Node_coordinates));
    piece->x = x;
    piece->y = y;
    piece->next = NULL;
    linked_list->head = piece;
  }
}

void freeNodes(Linked_list *linked_list)
{
  free(linked_list);
}
