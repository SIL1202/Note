#include <iostream>

class Node {
public:
  Node() : next(nullptr), prev(nullptr) {}
  Node(int d) : data(d), next(nullptr), prev(nullptr) {}

  int data;
  Node *next;
  Node *prev;
};

class DLL {
public:
  DLL() : head(nullptr), tail(nullptr) {}

  void insert(int d) {
    Node *newNode = new Node(d);
    if (!head) {
      head = tail = newNode;
    } else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  void print() {
    Node *temp = head;
    while (temp) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }

  void reverseDLL() {
    Node *temp = nullptr;
    Node *current = head;
    while (current) {
      temp = current->prev;
      current->prev = current->next;
      current->next = temp;
      current = current->prev;
    }

    if (temp) {
      head = temp->prev;
    }
  }

private:
  Node *head;
  Node *tail;
};

int main() {
  DLL list;
  list.insert(0);
  list.insert(1);
  list.insert(2);
  list.insert(3);
  list.insert(4);
  list.print();
  list.reverseDLL();
  list.print();
  return 0;
}
