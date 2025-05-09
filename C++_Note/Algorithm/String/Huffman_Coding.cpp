#include <iostream>
#include <map>
#include <queue>
#include <string>

struct HuffmanNode {
  char character;
  int frequency;
  HuffmanNode *left, *right;

  HuffmanNode(char ch, int freq)
      : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
  HuffmanNode(int freq, HuffmanNode *l, HuffmanNode *r)
      : character('\0'), frequency(freq), left(l), right(r) {}

  ~HuffmanNode() {
    delete left;
    delete right;
  }
};

struct Compare {
  bool operator()(HuffmanNode *a, HuffmanNode *b) {
    if (a->frequency != b->frequency) {
      return a->frequency > b->frequency;
    }
    return a->character > b->character;
  }
};

void buildCodes(HuffmanNode *root, std::string code,
                std::map<char, std::string> &codes) {
  if (!root->left && !root->right) {
    codes[root->character] = code;
    return;
  }
  if (root->left)
    buildCodes(root->left, code + "0", codes);
  if (root->right)
    buildCodes(root->right, code + "1", codes);
}

std::map<char, std::string> huffmanCoding(const std::string &text) {
  if (text.empty())
    return {};

  // 統計頻率
  std::map<char, int> freq;
  for (char c : text)
    freq[c]++;

  // 建堆
  std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, Compare>
      codes_map;
  for (auto &[ch, count] : freq) {
    codes_map.push(new HuffmanNode(ch, count));
  }

  // 處理單一字元情況
  if (codes_map.size() == 1) {
    auto root = codes_map.top();
    std::map<char, std::string> codes;
    codes[root->character] = "0";
    delete root;
    return codes;
  }

  // 合併樹
  while (codes_map.size() > 1) {
    auto left = codes_map.top();
    codes_map.pop();
    auto right = codes_map.top();
    codes_map.pop();
    auto parent =
        new HuffmanNode(left->frequency + right->frequency, left, right);
    codes_map.push(parent);
  }

  // 生成編碼
  std::map<char, std::string> codes;
  buildCodes(codes_map.top(), "", codes);
  delete codes_map.top(); // 釋放整棵樹
  return codes;
}

int main() {
  // 測試案例 1: 一般情況
  std::string text1 = "abracadabra";
  std::map<char, std::string> codes1 = huffmanCoding(text1);

  std::cout << "Huffman Codes for \"" << text1 << "\":" << std::endl;
  for (const auto &[ch, code] : codes1) {
    std::cout << "'" << ch << "': " << code << std::endl;
  }
  std::cout << std::endl;

  // 測試案例 2: 單一字元情況
  std::string text2 = "aaaaa";
  std::map<char, std::string> codes2 = huffmanCoding(text2);

  std::cout << "Huffman Codes for \"" << text2 << "\":" << std::endl;
  for (const auto &[ch, code] : codes2) {
    std::cout << "'" << ch << "': " << code << std::endl;
  }
  std::cout << std::endl;

  // 測試案例 3: 空字串
  std::string text3 = "";
  std::map<char, std::string> codes3 = huffmanCoding(text3);

  std::cout << "Huffman Codes for empty string:" << std::endl;
  if (codes3.empty()) {
    std::cout << "(No codes generated)" << std::endl;
  }
  std::cout << std::endl;

  // 測試案例 4: 混合字元
  std::string text4 = "hello world";
  std::map<char, std::string> codes4 = huffmanCoding(text4);

  std::cout << "Huffman Codes for \"" << text4 << "\":" << std::endl;
  for (const auto &[ch, code] : codes4) {
    std::cout << "'" << ch << "': " << code << std::endl;
  }

  return 0;
}
