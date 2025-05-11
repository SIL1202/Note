# 🧩 Disjoint Set / Union-Find 筆記

## 📌 概念說明

**Disjoint Set** 是一種資料組織，用來處理 **不重疏集合**（Disjoint Sets）之間的合併與查詢問題。主要支援以下兩個操作：

* `find(x)`：查詢元素 `x` 所屬集合的代表（root）

  ```cpp
  int find(int x){
    return root[x];
  }
  ```

  

* `union(x, y)`：合併 `x` 與 `y` 所在的兩個集合

  ```cpp
  void unionSet(int x, int y) {
    int rootX = find(x);
  	int rootY = find(y);
      if (rootX != rootY) {
  			for (int i = 0; i < root.size(); i++) {
          if (root[i] == rootY)
            root[i] = rootX;
        }
      }
  }
  ```

  

這組織特別適合用於：

* 動態連通性問題（如圖的連通塊判斷）
* Kruskal 最小生成樹（MST）演算法
* 判斷是否成為一個環（Cycle Detection）

---

## 🛠️ 常見優化技巧

1. **Path Compression**：加速 `find()` 查詢，讓每個節點指向其最終根節點

   ```cpp
   int find(int x){
     if(root[x] == x) 
       return x;
     return root[x] = find(root[x]);
   }
   ```

2. **Union by Rank / Size**：合併時讓小集合掛到大集合，降低樹高

   ```cpp
   void UnoinSet(int x, int y){
     int rootX = find(x);
     int rootY = find(y);
     if(rootX != rootY){
       root[rootY] = rootX;
     }
   }
   ```



---

## 💡 使用情境範例

* 判斷任意兩點是否同屬一個群組（connected component）
* 記錄社交圈（朋友圈合併問題）
* 避免連成環（Cycle detection）

---

## 🧪 C++ 範例程式碼

```cpp
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
public:
  UnionFind(int sz) : root(sz) {
    for (int i = 0; i < sz; i++) root[i] = i;
  }

  int find(int x) {
    return root[x];  // 無優化版本
  }

  void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) { 
      for (int i = 0; i < root.size(); i++) { // 無優化版本
        if (root[i] == rootY)
          root[i] = rootX;
      }
    }
  }

  bool connected(int x, int y) {
    return find(x) == find(y);
  }

private:
  vector<int> root;
};
```

---

## 📦 測試資料

```cpp
int main() {
  cout << boolalpha;
  UnionFind uf(10);
  // 1-2-5-6-7 3-8-9 4
  uf.unionSet(1, 2);
  uf.unionSet(2, 5);
  uf.unionSet(5, 6);
  uf.unionSet(6, 7);
  uf.unionSet(3, 8);
  uf.unionSet(8, 9);

  cout << uf.connected(1, 5) << endl; // true
  cout << uf.connected(5, 7) << endl; // true
  cout << uf.connected(4, 9) << endl; // false

  // 合併 4 與 9
  uf.unionSet(9, 4);
  cout << uf.connected(4, 9) << endl; // true
}
```

------

## 🧠 時間複雜度分析

### ⏱️ `find(x)` 時間複雜度分析

- 最差情況下：節點可能需要查找多層父節點
- 加入路徑壓縮後：幾乎所有節點都會直接連接到根節點

### ⚡ 總體複雜度

對於 `n` 筆操作，整體時間複雜度為：

$O(α(n))$

其中 α(n) 是反阿克曼函數，增長極慢：

- $α(1)=1$
- $α(10)=2$
- $α(2^{2^{16}}) = 5$

➡️ 所以實務上可視為 **近乎 O(1)** 的操作

| 操作類型     | 無優化 | 有 Path Compression |
| ------------ | ------ | ------------------- |
| `find(x)`    | O(n)   | O(α(n)) ≈ O(1)      |
| `union(x,y)` | O(n)   | O(α(n)) ≈ O(1)      |
| 總體操作     | O(n²)  | O(n·α(n))           |

------

## 📟 結說

Disjoint Set 是處理動態連通性問題非常高效的工具。在競賽與圖論演算法中常見。建議實作熟習並加上優化技巧，才能應對大型資料量。
