# 樹的直徑（Tree Diameter）

## 一、定義

**樹的直徑（Diameter of a Tree）** 是指：

> 在一棵樹中，**距離最遠的兩個節點之間的最長簡單路徑長度**。

這條路徑稱為「直徑路徑」。直徑可能**不經過 root**，甚至通常不會經過 root。

---

## 二、常見求法（兩次 DFS / BFS）

### 🎯 步驟：

1. 從任意節點執行 DFS，找出**最遠的節點 \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*`u`**。
2. 從 `u` 出發再 DFS 一次，找出距離最遠的節點 `v`，其距離即為直徑。

這是因為：

* 第一次 DFS 會找到某個「邊界」節點 `u`
* 從邊界再出發一定能找到全圖最遠的另一端 `v`

---

## 三、程式碼實作（C++，無權樹）

```cpp
#include <iostream>
#include <vector>
using namespace std;

#define pb push_back
const int MAX = 2e5 + 5;
int n;
vector<int> adj[MAX];
vector<int> vis;
int maxD, maxNode;

void dfs(int v, int d) {
  vis[v] = true;
  if (d > maxD)
    maxD = d, maxNode = v;
  for (int u : adj[v]) {
    if (!vis[u]) {
      dfs(u, d + 1);
    }
  }
};

int main() {
  cin >> n;
  vis.assign(n + 1, false);
  int a, b;
  for (int i = 0; i < n - 1; i++)
    cin >> a >> b, adj[a].pb(b), adj[b].pb(a);

  maxD = -1;
  dfs(1, 0);

  vis.assign(n + 1, false);
  maxD = -1;
  dfs(maxNode, 0);

  cout << maxD << '\n';
}
```

---

## 四、常見問題

### Q1：為什麼要做兩次 DFS？

因為只有從「邊界」節點出發，才能找到另一端的最長距離。隨便從 root 出發不一定能達成。

### Q2：直徑會經過 root 嗎？

不一定。大多數情況下，**root 不會在直徑上**。直徑只取決於最遠兩點，與 root 無關。

---

## 五、延伸應用

* 找出直徑長度（最遠距離）
* 找出直徑的端點（紀錄 `farthestNode`）
* 樹中心（tree center）在直徑路徑中間節點
* 轉為 DP 求每點最遠子樹深度（如 CSES Tree Distances）

---

## 六、例題整理

### ✅ SPOJ - [PT07Z - Longest path in a tree](https://www.spoj.com/problems/PT07Z/)

* **題目描述**：給定一棵無向樹，輸出其直徑（最長路徑長度）

* **重點**：輸出最遠距離，不需要輸出節點或路徑

* 解法程式碼：

  ```cpp
  #include <iostream>
  #include <vector>
  using namespace std;
  
  const int MAX = 1e5 + 5;
  int n;
  vector<int> adj[MAX];
  vector<int> vis, dis;
  
  int maxlength = -1;
  int farthestNode = 1;
  
  void dfs(int v) {
    vis[v] = true;
    for (int u : adj[v]) {
      if (!vis[u]) {
        dis[u] = dis[v] + 1;
        if (dis[u] > maxlength) {
          maxlength = dis[u];
          farthestNode = u;
        }
        dfs(u);
      }
    }
  }
  
  int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
      int a, b;
      cin >> a >> b;
      adj[a].push_back(b);
      adj[b].push_back(a);
    }
  
    // 第一次 DFS：任意節點出發找最遠點
    vis.assign(n + 1, false);
    dis.assign(n + 1, 0);
    maxlength = -1;
    dfs(1);
  
    // 第二次 DFS：從最遠點出發找最大距離
    vis.assign(n + 1, false);
    dis.assign(n + 1, 0);
    maxlength = -1;
    dfs(farthestNode);
  
    cout << maxlength << '\n';
    return 0;
  }
  ```

  

### ✅ CSES - [Tree Diameter](https://cses.fi/problemset/task/1131)

* **題目描述**：給定一棵樹，輸出其直徑長度
* **解法程式碼**：

```cpp
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

#define pb push_back
const int MAX = 2e5 + 5;

int main() {
  int n;
  cin >> n;
  vector<int> adj[MAX];
  vector<int> vis(n + 1, false);
  int a, b;
  for (int i = 0; i < n - 1; i++)
    cin >> a >> b, adj[a].pb(b), adj[b].pb(a);

  int maxD, maxNode;
  function<void(int, int)> dfs = [&](int v, int d) -> void {
    vis[v] = true;
    if (d > maxD)
      maxD = d, maxNode = v;
    for (int u : adj[v]) {
      if (!vis[u]) {
        dfs(u, d + 1);
      }
    }
  };

  maxD = -1;
  dfs(1, 0);

  vis.assign(n + 1, false);
  maxD = -1;
  dfs(maxNode, 0);

  cout << maxD << '\n';
}
```

