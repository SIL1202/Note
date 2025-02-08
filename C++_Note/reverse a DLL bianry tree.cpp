#include <iostream>

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
}
