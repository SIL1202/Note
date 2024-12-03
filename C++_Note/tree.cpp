struct Node {
  int data;
  Node *right;
  Node *left;
};

Node *createNode(int data) {
  Node *new_node = new Node();
  new_node->data = data;
  new_node->right = new_node->left = nullptr;
  return new_node;
}

int main() {
  Node *root = createNode(1);
  root->right = createNode(2);
  root->left = createNode(3);
  root->left->left = createNode(4);
  return 0;
}
