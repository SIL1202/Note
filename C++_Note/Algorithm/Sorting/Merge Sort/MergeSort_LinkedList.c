#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

Node *mergeSort(Node *);
Node *split(Node *node);
Node *merge(Node *first, Node *second);
void printList(Node *);

int main() {
  Node *head = malloc(sizeof(Node));
  head->data = 3;
  head->next = malloc(sizeof(Node));
  head->next->data = 2;
  head->next->next = malloc(sizeof(Node));
  head->next->next->data = 1;
  head->next->next->next = NULL;

  head = mergeSort(head);
  printList(head);
  return 0;
}

Node *split(Node *head) {
  Node *fast = head, *slow = head, *prev = NULL;
  while (fast && fast->next) {
    fast = fast->next->next;
    prev = slow;
    slow = slow->next;
  }
  if (prev)
    prev->next = NULL;
  return slow;
}

// 1 2 3 4
// 1 2 3 4 5

Node *mergeSort(Node *head) {
  if (!head || !head->next)
    return head;

  Node *second = split(head);

  head = mergeSort(head);
  second = mergeSort(second);

  return merge(head, second);
}

Node *merge(Node *first, Node *second) {
  if (!first)
    return second;
  if (!second)
    return first;

  Node *result = NULL;
  if (first->data < second->data) {
    result = first;
    first->next = merge(first->next, second);
  } else {
    result = second;
    second->next = merge(first, second->next);
  }
  return result;
}

void printList(Node *head) {
  Node *cur = head;
  while (cur) {
    printf("%d ", cur->data);
    cur = cur->next;
  }
  printf("\n");
}
