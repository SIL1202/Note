#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Trie {
private:
  Trie *children[26];
  bool endOfword;

public:
  Trie() {
    for (int i = 0; i < 26; i++) {
      children[i] = nullptr;
    }
    endOfword = false;
  }

  void Trie_insert(string word) {
    Trie *root = this;

    for (char c : word) {
      int index = c - 'a';
      if (!root->children[index]) {
        root->children[index] = new Trie();
      }
      root = root->children[index];
    }
    root->endOfword = true;
  }

  vector<string> autocomplete(string prefix) {
    Trie *current = this;
    for (char c : prefix) {
      int index = c - 'a';
      if (!current->children[index])
        return {}; // 前綴不存在，返回空
      current = current->children[index];
    }

    // 遞迴收集所有以該節點為起點的單詞
    vector<string> result;
    collectWords(current, prefix, result);
    return result;
  }

private:
  void collectWords(Trie *node, string prefix, vector<string> &result) {
    if (node->endOfword) {
      result.push_back(prefix); // 如果是單詞的結尾，加入結果
    }
    for (int i = 0; i < 26; i++) {
      if (node->children[i]) {
        collectWords(node->children[i], prefix + char('a' + i), result);
      }
    }
  }
};

int main() {
  Trie *root = new Trie();

  root->Trie_insert("apple");
  root->Trie_insert("application");
  root->Trie_insert("applet");
  root->Trie_insert("banana");
  root->Trie_insert("band");

  vector<string> suggestions = root->autocomplete("app");
  cout << "Autocomplete suggestions for 'app':" << endl;
  for (string word : suggestions) {
    cout << "- " << word << endl;
  }

  delete root;
  return 0;
}
