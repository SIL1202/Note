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
   // Rank 按照樹高
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
   
   // 或可以簡寫成以下形式
   void unionSet(int x, int y) {
     int rootX = find(x);
     int rootY = find(y);
     if (rootX == rootY) return; // 已經在同一個集合，直接返回
   
     // 確保 rootX 是較大的樹（如果 rank 相同，則無所謂）
     if (rank[rootX] < rank[rootY]) {
       swap(rootX, rootY);
     }
   
     // 合併較小的樹 (rootY) 到較大的樹 (rootX)
     root[rootY] = rootX;
   
     // 如果兩棵樹 rank 相同，則增加 rootX 的 rank
     if (rank[rootX] == rank[rootY]) {
       rank[rootX]++;
     }
   }
   ```

   ```cpp
   // Size 按照 component size
   void unionSet(int x, int y) {
     int rootX = find(x);
     int rootY = find(y);
     if (rootX == rootY) return;  // 已在同一集合，直接返回
   
     // 確保 rootX 是較大的集合
     if (size[rootX] < size[rootY]) {
       swap(rootX, rootY);
     }
   
     // 合併較小的集合 (rootY) 到較大的集合 (rootX)
     root[rootY] = rootX;
     size[rootX] += size[rootY];  // 更新集合大小
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

------

## 📌 解法範例題

### 🔹 [CSES - Road Construction](https://cses.fi/problemset/task/1676)

**題目描述：**
每次加入一條邊後，輸出當前圖中連通元件數量與最大元件大小。

**解法：** 使用 DSU，維護：

- `components`：當前集合數量（初始為 n，每合併一次 -1）
- `size[]`：每個 root 的元件大小
- `largest`：目前最大元件大小

**程式邏輯：**

```cpp
#include <iostream>
#include <vector>
using namespace std;

class US {
public:
  US(int n) : largest(0), component(n), parent(n + 1), size(n + 1, 1) {
    for (int i = 1; i <= n; i++) {
      parent[i] = i;
    }
  }

  int find(int x) {
    if (parent[x] == x)
      return x;

    return parent[x] = find(parent[x]);
  }

  void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX == rootY)
      return;
    ;

    component--;
    if (size[rootX] < size[rootY])
      swap(rootX, rootY);
    parent[rootY] = rootX;
    size[rootX] += size[rootY];
    largest = max(size[rootX], largest);
  }

  int largest, component;

private:
  vector<int> parent, size;
};
```

每次讀入邊後：

```cpp
const int MAX = 1e5 + 1;
int main() {
  int n, m;
  cin >> n >> m;

  US uf(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    uf.unite(x, y);
    cout << uf.component << ' ' << uf.largest << '\n';
  }
  return 0;
}
```

------

### 🔹 [Hackerrank - Components in a Graph](https://www.hackerrank.com/challenges/components-in-graph/problem)

**題目描述：**
給定一個無向圖，每個節點為 a_i 和 b_i 的連接，輸出所有 connected component 的最小與最大大小（只包含大小 >= 2 的 component）。

**解法：**

- 使用 DSU 將所有節點合併（注意 id 可能不連續）
- 最後統計每個 root 的元件大小，取其中大小 ≥ 2 的 min 和 max

------

## 🧠 補充觀念

- 使用 `iota()` 快速初始化 parent：

  ```cpp
  iota(parent, parent + n + 1, 0);
  ```

- 避免重複合併：在 `unite()` 裡一定加上：

  ```cpp
  if (a == b) return;
  ```

- 如果想維護 rank 但不追 size：可以用 `rank[]` 實作 union by rank

------

## 🗂 題目整理表

| 題目                  | 平台       | 類型         | 關鍵技巧                     |
| --------------------- | ---------- | ------------ | ---------------------------- |
| Road Construction     | CSES       | 動態連通性   | DSU + size + component count |
| Components in a Graph | Hackerrank | 基礎合併統計 | DSU + map root size          |

