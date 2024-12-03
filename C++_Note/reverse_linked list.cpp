#include <iostream>
using namespace std;

struct Node {
  int value;
  Node *next;
  Node(int val) : value(val), next(nullptr) {}
};

void printList(Node *head) {
  while (head != nullptr) {
    cout << head->value << " ";
    head = head->next;
  }
  cout << endl;
}

Node *reverseList(Node *head) {
  Node *prev = nullptr;
  Node *current = head;
  Node *next = nullptr;

  while (current != nullptr) {
    next = current->next; // 暫存下一個節點
    current->next = prev; // 反轉當前節點的 next 指針
    prev = current;       // 移動 prev 指針
    current = next;       // 移動 current 指針
  }
  head = prev; // 更新 head 為新的頭節點
  return head;
}

int main() {
  Node *head = new Node(1);
  head->next = new Node(2);
  head->next->next = new Node(3);
  head->next->next->next = new Node(4);

  cout << "Original List: ";
  printList(head);

  head = reverseList(head);

  cout << "Reversed List: ";
  printList(head);

  return 0;
}
