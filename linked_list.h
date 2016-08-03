#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node_coordinates
{
  int x, y;
  struct Node_coordinates *next;
} Node_coordinates;

typedef struct Linked_list
{
  Node_coordinates *head;
} Linked_list;

Linked_list* createLinkedList();
void addNode(Linked_list *linked_list, int x, int y);
size_t count(Linked_list *linked_list);
void freeNodes(Linked_list *linked_list);

#endif