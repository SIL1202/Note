# Huffman Coding 筆記

## 什麼是 Huffman Coding？

Huffman Coding 是一種可變長度編碼的壓縮演算法，用來根據字元出現頻率設計最短編碼方式，達到節省空間的目的。

------

## 核心概念

- 每個字元的出現頻率（frequency）影響它的編碼長度。
- 出現越頻繁的字元 → 編碼越短。
- 編碼結果是一棵 **prefix-free binary tree**（無前綴編碼樹）。

------

## Huffman Tree 建構流程

1. 計算每個字元出現次數。

   ```cpp
   std::map<char, int> ch_count;
   for(char c: text){
   	if(ch_count.find(c) == ch_count.end()) // 沒找到
       ch_count[c] = 1;
     else 
       ch_count[c] ++: // 找到
   }
   ```

   

2. 將每個字元視為一個節點放入 priority queue（小根堆，依頻率排序）。

```cpp
struct node_compare{
  bool operator()(const HuffmanNode ＊a, const HuffmanNode *b){
    if(a->frequency ！= b->frequency)
      return a->frequency > b->frequency;
    return a->character > b->character; // 平局時，按字元順序（或其他規則）決定
  }
};

std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, node_compare> trees;
```

3. 每次取出兩個頻率最小的節點，合併成一個新的節點（作為它們的父節點）。

1. ```cpp
   trees.push(new HuffmanNode(left->frequency + right->frequency, left, right)); // add two childs node's frequency into parent node
   ```

   

2. 重複直到只剩一個根節點 → 成為 Huffman Tree。

   ```cpp
   if(trees.empty()){
   	root = left;
   	break;
   }
   ```

   

3. 從根節點開始遞迴遍歷：

   ```cpp
   void buildCodes(HuffmanNode* root, std::string code, std::map<char, std::string>& codes) {
       if (!root->left && !root->right) {
           codes[root->character] = code;
           return;
       }
       if (root->left) buildCodes(root->left, code + "0", codes);
       if (root->right) buildCodes(root->right, code + "1", codes);
   }
   ```

   - 左子節點 → 加上 "0"
   - 右子節點 → 加上 "1"

------

## 特殊情況處理

- 如果字串中只有**一種字元**，Huffman Tree 只有一個節點，無法產生 "0/1" 路徑。
  - 解法：若編碼為空字串，強制指定為 "0"，以保證至少有一個 bit。
  
    ```cpp
    if(trees.size() == 1){
    	HuffmanNode* root = trees.top();
      trees.pop();
      codes_map[root->character] = "0";
    	delete root;
      return codes_map;
    }
    ```
  
    

## C++ 關鍵技巧

- 使用 `priority_queue<Node*, vector<Node*>, Compare>` 做小根堆。

- 使用 struct 中的 destructor 遞迴刪除整棵樹：

  ```cpp
  ~HuffmanNode() {
    delete left_child;
    delete right_child;
  }
  ```

- 只要最後對 `root` 執行 `delete root;`，整棵樹的記憶體就會遞迴釋放。

------

## 常見錯誤

- 編碼表中每個字元只加一次 → 忽略出現次數
- 忘記釋放記憶體 → 應該 `delete root;`
- 單一字元時未處理空編碼 → 應該補上 `code[ch] = "0"`

------

## 小結

Huffman Coding 是經典且高效的壓縮演算法，適合處理文字或符號頻率差異明顯的資料，結合 heap 結構與樹的遞迴技巧能完成完整的壓縮流程。

## 完整程式碼

```cpp
#include <queue>
#include <map>
#include <string>

struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *left, *right;
    
    HuffmanNode(char ch, int freq) : character(ch), frequency(freq), left(nullptr), right(nullptr) {}
    HuffmanNode(int freq, HuffmanNode* l, HuffmanNode* r) : character('\0'), frequency(freq), left(l), right(r) {}
    
    ~HuffmanNode() {
        delete left;
        delete right;
    }
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        if (a->frequency != b->frequency) {
            return a->frequency > b->frequency;
        }
        return a->character > b->character;
    }
};

void buildCodes(HuffmanNode* root, std::string code, std::map<char, std::string>& codes) {
    if (!root->left && !root->right) {
        codes[root->character] = code;
        return;
    }
    if (root->left) buildCodes(root->left, code + "0", codes);
    if (root->right) buildCodes(root->right, code + "1", codes);
}

std::map<char, std::string> huffmanCoding(const std::string& text) {
    if (text.empty()) return {};
    
    // 統計頻率
    std::map<char, int> freq;
    for (char c : text) freq[c]++;
    
    // 建堆
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, Compare> codes_map;
    for (auto& [ch, count] : freq) {
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
        auto parent = new HuffmanNode(left->frequency + right->frequency, left, right);
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
    for (const auto& [ch, code] : codes1) {
        std::cout << "'" << ch << "': " << code << std::endl;
    }
    std::cout << std::endl;

    // 測試案例 2: 單一字元情況
    std::string text2 = "aaaaa";
    std::map<char, std::string> codes2 = huffmanCoding(text2);
    
    std::cout << "Huffman Codes for \"" << text2 << "\":" << std::endl;
    for (const auto& [ch, code] : codes2) {
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
    for (const auto& [ch, code] : codes4) {
        std::cout << "'" << ch << "': " << code << std::endl;
    }

    return 0;
}
```

