#include <iostream>
/*
template <typename T> struct Node {
  T data;
  Node *left;
  Node *right;

  Node(T d) : data(d), left(nullptr), right(nullptr) {}
};

template <typename T> class BST {
public:
  BST() : node(nullptr) {}

  ~BST() {
    this->destroy(this->node); // 呼叫遞迴刪除函式
  }

  void insert(T data) { this->node = this->insertion(this->node, data); }

  void print() {
    this->inorder(this->node);
    std::cout << std::endl;
  }

private:
  Node<T> *node;

  Node<T> *insertion(Node<T> *node, T data) {
    if (node == nullptr) {
      return new Node<T>(data);
    }
    if (data < node->data) {
      node->left = this->insertion(node->left, data);
    } else if (data > node->data) {
      node->right = this->insertion(node->right, data);
    }
    return node;
  }

  void inorder(Node<T> *node) {
    if (node == nullptr)
      return;
    this->inorder(node->left);
    std::cout << node->data << " ";
    this->inorder(node->right);
  }

  void destroy(Node<T> *node) {
    if (node == nullptr)
      return;
    this->destroy(node->left);  // 先刪左子樹
    this->destroy(node->right); // 再刪右子樹
    delete node;                // 最後刪自己
  }
};

int main() {
  BST<int> tree;
  tree.insert(1);
  tree.insert(4);
  tree.insert(3);
  tree.insert(6);
  tree.insert(9);
  tree.insert(2);
  tree.print(); // 輸出：1 2 3
  return 0;
} */

struct Node {
  int data;
  Node *next;
  Node *prev;

  Node() : next(nullptr), prev(nullptr) {}
  Node(int d) : data(d), next(nullptr), prev(nullptr) {}
};

class DLL {
public:
  DLL() {
    this->head = nullptr;
    this->tail = nullptr;
  }

  void insert(int data) {
    Node *newNode = new Node(data);
    if (head == nullptr)
      head = tail = newNode;
    else {
      tail->next = newNode;
      newNode->prev = tail;
      tail = newNode;
    }
  }

  void remove(int data) {
    Node *temp = head;
    while (temp && temp->data != data) {
      temp = temp->next;
    }

    if (!temp)
      return;
    if (temp == head)
      head = temp->next;
    if (temp == tail)
      tail = temp->prev;

    if (temp->prev)
      temp->prev->next = temp->next;
    if (temp->next)
      temp->next->prev = temp->prev;

    delete temp;
  }

  void printForward() {
    Node *temp = head;
    while (temp) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
  }

  void printBackward() {
    Node *temp = tail;
    while (temp) {
      std::cout << temp->data << " ";
      temp = temp->prev;
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

  list.printForward();
  std::cout << "\n";
  list.printBackward();
  return 0;
}
