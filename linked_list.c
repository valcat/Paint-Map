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

size_t count(Linked_list *linked_list) 
{
  size_t count = 0;
  Node_coordinates *indexNode = linked_list->head;
  while (indexNode) {
    count++;
    indexNode = indexNode->next;
  }
  return count;
}

Node_coordinates* get_by_index(Linked_list *linked_list, int index)
{
  size_t count = 0;
  Node_coordinates *indexNode = linked_list->head;
  while (indexNode) {
    if (count == index) {
      return indexNode;
    }
    indexNode = indexNode->next;
    count++;
  }
}

void freeNodes(Linked_list *linked_list)
{
  free(linked_list);
}
