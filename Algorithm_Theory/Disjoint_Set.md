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
   void unionSet(int x, int y) {
       int rootX = find(x);
       int rootY = find(y);
       if (rootX != rootY) {
         if (rank[rootX] > rank[rootY])
           root[rootY] = rootX;
         else if (rank[rootX] < rank[rootY])
           root[rootX] = rootY;
         else {
           root[rootY] = rootX;
           rank[rootX]++;
         }
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
  // 建構函式：初始化 root 和 rank 陣列
  UnionFind(int sz) : root(sz), rank(sz) {
    for (int i = 0; i < sz; i++) {
      root[i] = i;   // 每個節點初始為自己的根
      rank[i] = 1;   // 每棵樹初始高度為 1
    }
  }

  // find：尋找 x 的根節點，並路徑壓縮
  int find(int x) {
    if (root[x] == x)
      return x;
    return root[x] = find(root[x]);  // 路徑壓縮：直接連到根節點
  }

  // unionSet：合併 x 與 y 的集合（用 rank 判斷樹高）
  void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      if (rank[rootX] > rank[rootY])      // x 的樹比較高，y 接到 x
        root[rootY] = rootX;
      else if (rank[rootX] < rank[rootY]) // y 的樹比較高，x 接到 y
        root[rootX] = rootY;
      else {                              // 高度相等，隨便接並更新高度
        root[rootY] = rootX;
        rank[rootX]++;
      }
    }
  }

  // 檢查兩節點是否屬於同一集合
  bool connected(int x, int y) { return find(x) == find(y); }

private:
  vector<int> root; // 紀錄每個節點的父節點
  vector<int> rank; // 紀錄每個集合樹的高度
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

### ⚡ 總體複雜度比較

| 優化方式                | `find`/`union` 單次時間複雜度 |
| ----------------------- | ----------------------------- |
| 無優化                  | O(n)                          |
| 只有 Rank               | O(log n)                      |
| Path Compression        | 接近 O(log n)                 |
| Rank + Path Compression | **O(α(n)) ≈ O(1)**            |

### 📌 說明：

- 若只用 rank（不含壓縮），最壞情況樹高為 $log⁡n$，所以 `find` 為 $O(log⁡n)$
- 若加入路徑壓縮，則整體摺疊效率變高，複雜度下降為 $O(α(n))$
- $α(n)$ 是反阿克曼函數，成長極慢，在實務中可視為常數時間

$α(1)=1,\ α(10)=2,\ α(2^{2^{16}})=5$

➡️ 因此 Path Compression + Rank 是最理想的優化組合。

------

## 📟 結說

Disjoint Set 是處理動態連通性問題非常高效的工具。在競賽與圖論演算法中常見。建議實作熟習並加上優化技巧，才能應對大型資料量。
