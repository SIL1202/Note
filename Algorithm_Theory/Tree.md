# 判斷圖是否為樹（Tree）

## 一、樹的基本定義

在圖論中，**樹（Tree)** 是一種特殊的圖，滿足以下性質：

### ✅ 無向圖的樹定義：

1. 連通（Connected）
2. 無環（Acyclic）
3. 對於 n 個節點，一定有 n - 1 條邊

➡ 若上述三個條件成立，則為一棵樹。

### ✅ 有向圖的樹定義（有向樹 / rooted tree）：

1. 只有一個節點入度為 0（root）
2. 其他每個節點入度為 1
3. 從 root 出發可以走訪所有節點（單向連通）
4. 無環（不能回到自己）
5. 邊數 = 節點數 - 1

---

## 二、無向圖判斷是否為樹

### 🎯 判斷條件：

* 邊數是否為 n - 1
* DFS 或 BFS 是否可以從任意節點訪問所有節點（確認連通）

---

### 📘 範例：SPOJ - Is it a tree?

* **題目簡述**：給一個無向圖，判斷其是否為一棵樹。
* **解題思路**：確認連通性、邊數為 n - 1。
* **完整程式碼**：

```cpp
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

const int MAX = 1e5 + 5;

int main() {
  int n, m;
  cin >> n >> m;
  vector<int> vis(n + 1, false);
  vector<int> adj[MAX];

  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a); // 無向圖雙向邊
  }

  function<void(int)> dfs = [&](int x) {
    vis[x] = true;
    for (int v : adj[x]) {
      if (!vis[v]) dfs(v);
    }
  };

  dfs(1); // 從節點 1 開始 DFS

  int count = 0;
  for (int i = 1; i <= n; ++i)
    if (vis[i]) count++;

  if (count == n && m == n - 1)
    cout << "YES\n"; // 是樹
  else
    cout << "NO\n"; // 不是樹

  return 0;
}
```

---

## 三、有向圖判斷是否為樹（Rooted Tree）

### 🎯 判斷條件：

1. 入度為 0 的節點數量為 1（作為 root）
2. 其餘節點入度皆為 1
3. 從 root 出發 DFS / BFS 可遍歷所有節點
4. 無循環
5. 邊數為 n - 1

---

### ✅ 範例函式：

```cpp
bool isDirectedTree(const vector<vector<int>>& adj, int n) {
  vector<int> in_deg(n + 1, 0);
  vector<bool> visited(n + 1, false);

  // 計算入度
  for (int u = 1; u <= n; ++u) {
    for (int v : adj[u]) {
      in_deg[v]++;
    }
  }

  int root = -1;
  for (int i = 1; i <= n; ++i) {
    if (in_deg[i] == 0) {
      if (root != -1) return false; // 多於一個 root
      root = i;
    }
  }

  if (root == -1) return false; // 無 root

  // DFS 判斷連通性與有無 cycle
  function<bool(int)> dfs = [&](int u) {
    visited[u] = true;
    for (int v : adj[u]) {
      if (visited[v]) return false; // cycle found
      if (!dfs(v)) return false;
    }
    return true;
  };

  if (!dfs(root)) return false;

  // 檢查是否所有節點都訪問過
  for (int i = 1; i <= n; ++i) {
    if (!visited[i] && in_deg[i] > 0)
      return false;
  }

  return true;
}
```

📝 **提醒：有向圖的範例可以參考未來題目如** CSES - Company Queries（或樹狀結構題目）

---

## 四、總結對照表

| **項目**      | **無向圖**        | **有向圖（Rooted Tree）**      |
| ----------- | -------------- | ------------------------- |
| 邊數          | 必須為 n - 1      | 必須為 n - 1                 |
| 是否需要唯一 root | 否              | 是（入度為 0 的節點只能有一個）         |
| 是否連通        | 是，整體要能走遍       | 是，從 root 可走遍              |
| 是否有環        | 否              | 否                         |
| 判斷方法        | DFS/BFS + 邊數檢查 | 入度分析 + DFS/BFS + cycle 檢查 |

---



📌 補充練習題如：

* **Leetcode 261. [Graph Valid Tree](https://leetcode.com/problems/graph-valid-tree/description/)** (可到 [NeetCode](https://neetcode.io/problems/valid-tree) 練習)
* **CSES - [Company Queries 系列](https://cses.fi/problemset/task/1687)**（進階有向樹處理）
* **HackRank - [Is It A Tree?](https://www.hackerrank.com/contests/code-a-thon/challenges/is-it-a-tree/problem)**  (進階有向樹處理)
