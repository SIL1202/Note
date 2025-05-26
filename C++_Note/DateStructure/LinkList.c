// implement Linklist with c
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
  void *data;
  struct Node *next;
} Node;

typedef struct {
  Node *head;
  size_t dataSz;
} Linklist;

void initList(Linklist *list, size_t dataSz) { // constructor
  list->head = NULL;
  list->dataSz = dataSz;
}

void add(Linklist *list, void *data) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = malloc(list->dataSz);
  memcpy(newNode->data, data, list->dataSz);
  newNode->next = NULL;

  if (list->head == NULL) {
    list->head = newNode;
    return;
  }

  Node *current = list->head;
  while (current->next != NULL)
    current = current->next;
  current->next = newNode;
}

void print(Linklist *list, void (*printFunc)(void *)) {
  Node *current = list->head;
  while (current != NULL) {
    printFunc(current->data);
    current = current->next;
  }
}

void clearList(Linklist *list) {
  Node *current = list->head;
  while (current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp->data);
    free(temp);
  }
  list->head = NULL;
}

void printInt(void *data) { printf("%d ", *(int *)data); }

int main() {
  Linklist list;
  initList(&list, sizeof(int));

  int d1 = 0, d2 = 1, d3 = 2, d4 = 3;
  add(&list, &d1);
  add(&list, &d2);
  add(&list, &d3);
  add(&list, &d4);
  print(&list, printInt);
  clearList(&list);
  return 0;
}
