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

Linked_list* createLinkedList() 
{
  Linked_list *list = malloc(sizeof(Linked_list));
  
  return list;
}

void addNode(Linked_list *linked_list, void* x)
{
  Node *piece = NULL;

  if (linked_list->head) {
    Node *IndexNode = linked_list->head;

    while (IndexNode->next) {
      IndexNode = IndexNode->next;
    }
    piece = malloc(sizeof(Node));
    piece->element = x; 
    piece->next = NULL;
    IndexNode->next = piece;

  } else {
    piece = malloc(sizeof(Node));
    piece->element = x;
    piece->next = NULL;
    linked_list->head = piece;
  }
}

size_t count(Linked_list *linked_list) 
{
  size_t count = 0;
  Node *indexNode = linked_list->head;
  while (indexNode) {
    count++;
    indexNode = indexNode->next;
  }
  return count;
}

Node* getByIndex(Linked_list *linked_list, int index)
{
  size_t count = 0;
  Node *indexNode = linked_list->head;
  while (indexNode) {
    if (count == index) {
      return indexNode;
    }
    indexNode = indexNode->next;
    count++;
  }
}
