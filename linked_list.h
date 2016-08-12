#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node
{
  void* element;
  struct Node* next;
} Node;

typedef struct Linked_list
{
  Node* head;
} Linked_list;

Linked_list* createLinkedList();
void addNode(Linked_list* linked_list, void* x);
size_t count(Linked_list *linked_list);
void* getByIndex(Linked_list *linked_list, int index);

#endif