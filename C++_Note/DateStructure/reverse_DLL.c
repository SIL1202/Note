#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  void *data;
  struct Node *next;
  struct Node *prev;
} Node;

typedef struct DLL {
  Node *head;
  Node *tail;
} DLL;

void initDLL(DLL *dll) {
  dll->head = NULL;
  dll->tail = NULL;
}

void insert(DLL *dll, void *d) {
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = d;
  newNode->next = NULL;
  newNode->prev = NULL;

  if (!dll->head) {
    dll->head = dll->tail = newNode;
  } else {
    dll->tail->next = newNode;
    newNode->prev = dll->tail;
    dll->tail = newNode;
  }
}

void reverse(DLL *dll) {
  Node *temp = NULL;
  Node *current = dll->head;
  while (current != NULL) {
    temp = current->prev;
    current->prev = current->next;
    current->next = temp;
    current = current->prev;
  }
  if (temp) {
    dll->head = temp->prev;
  }
}

void print(DLL *dll, void (*printFunc)(void *)) {
  Node *current = dll->head;
  while (current != NULL) {
    printFunc(current->data);
    current = current->next;
  }
}

void printInt(void *data) { printf("%d ", *(int *)data); }

int main() {
  DLL dll;
  initDLL(&dll);
  int a = 10, b = 20, c = 30, d = 40;
  insert(&dll, &a);
  insert(&dll, &b);
  insert(&dll, &c);
  insert(&dll, &d);
  print(&dll, printInt);
  printf("\n");
  reverse(&dll);
  print(&dll, printInt);
}
