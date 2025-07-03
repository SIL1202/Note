#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUMBER 256
typedef struct TrieNode {
  struct TrieNode *children[MAX_NUMBER];
  bool terminal;
} TrieNode;

// create node for current layer of trie
TrieNode *createnode() {
  TrieNode *newNode = malloc(sizeof(TrieNode));
  for (int i = 0; i < MAX_NUMBER; ++i) {
    newNode->children[i] = NULL;
  }
  newNode->terminal = false;
  return newNode;
}

bool trieinsert(TrieNode **root, const char *text) { // text = signed text
  int n = strlen(text);
  unsigned char *utext = (unsigned char *)text; // utext = unsigned tex

  TrieNode *tmp = *root;
  for (int i = 0; i < n; ++i) {
    if (tmp->children[utext[i]] == NULL)
      tmp->children[utext[i]] = createnode();

    tmp = tmp->children[utext[i]];
  }

  if (tmp->terminal)
    return false;
  else
    return tmp->terminal = true;
}

void recur(TrieNode *node, unsigned char *prefix, int length) {
  unsigned char newprefix[length + 2];
  memcpy(newprefix, prefix, length);
  newprefix[length + 1] = 0;
  if (node->terminal) {
    printf("word: %s\n", prefix);
  }
  for (int i = 0; i < MAX_NUMBER; ++i) {
    if (node->children[i] != NULL) {
      newprefix[length] = i;
      recur(node->children[i], newprefix, length + 1);
    }
  }
}

void printtrie(TrieNode *root) {
  if (root == NULL) {
    printf("trie is empty\n");
    return;
  }
  TrieNode *node = root;

  unsigned char prefix[1024] = {0};
  recur(node, prefix, 0);
}

bool triesearch(const TrieNode *root, const char *text) {
  const TrieNode *node = root;
  const unsigned char *utext = (unsigned char *)text;
  const int n = strlen(text);
  for (int i = 0; i < n; ++i) {
    if (node->children[utext[i]] == NULL)
      return false;
    node = node->children[utext[i]];
  }
  return node->terminal;
}

bool deletestr(TrieNode **node, unsigned char *utext, int depth) {
  if (!node || !(*node))
    return false;

  TrieNode *cur = *node;
  if (utext[depth] == '\0') {
    if (!cur->terminal)
      return false;

    // return false if it has child node
    for (int i = 0; i < MAX_NUMBER; ++i)
      if (cur->children[i])
        return false;

    free(cur);
    *node = NULL; // set prev node to NULL
    return true;
  }

  if (deletestr(&cur->children[utext[depth]], utext, depth + 1)) {
    // if the child node has been deleted, check if the current node can be
    // deleted.
    if (!cur->terminal) {
      for (int i = 0; i < MAX_NUMBER; ++i)
        if (cur->children[i])
          return false;

      free(cur);
      *node = NULL;
      return true;
    }
  }
  return false; // default condition retrun false
}
bool deleteWrapper(TrieNode **root, const char *text) {
  return deletestr(root, (unsigned char *)text, 0);
}

void freetrie(TrieNode *node) {
  if (!node)
    return;
  for (int i = 0; i < MAX_NUMBER; ++i)
    if (node->children[i])
      freetrie(node->children[i]);
  free(node);
}

int main() {
  TrieNode *root = createnode();
  trieinsert(&root, "apple");
  trieinsert(&root, "banana");
  trieinsert(&root, "algorithm");
  trieinsert(&root, "bellmanford");
  printtrie(root);
  printf("\n");
  const char *text = "apple";
  if (triesearch(root, text))
    printf("%s exist\n", text);
  else
    printf("%s not exist\n", text);

  if (deleteWrapper(&root, text))
    printf("delete %s sucessfully\n", text);
  else
    printf("delete %s failed\n", text);

  if (triesearch(root, text))
    printf("%s exist\n", text);
  else
    printf("%s not exist\n", text);

  printf("\n");
  printtrie(root);
  freetrie(root);
  return 0;
}
