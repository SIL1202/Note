# Bipartite Graph 筆記

## 一、定義

Bipartite Graph（雙分圖，又稱 Bigraph）是一種特殊的無向圖，滿足以下條件：

1. 圖的所有節點可以被分成兩個**互斥集合**（Set A 和 Set B）。
2. 每條邊都必須連接這兩個集合中的**不同節點**。

   * 即：不能有邊連接同一個集合內的節點。

---

## 二、性質

* 一個圖是 Bipartite ⇔ **圖中沒有奇數長度的 cycle（奇環）**。
* 若可以將圖正確二染色（兩色上色使得相鄰節點異色），則圖為 Bipartite。

---

## 三、判斷演算法（DFS 著色）

```cpp
/**
 * Determines whether the given undirected graph is bipartite.
 * Uses DFS to attempt coloring each node with two colors (0 and 1).
 *
 * @param adj Adjacency list of the graph (1-based index)
 * @param n Number of nodes in the graph
 * @return true if the graph is bipartite, false otherwise
 */
bool isBipartite(vector<vector<int>>& adj, int n) {
  vector<int> color(n + 1, -1); // -1: unvisited, 0/1: two colors

  // Lambda function to perform DFS and try coloring
  function<bool(int, int)> dfs = [&](int u, int c) -> bool {
    color[u] = c;
    for (int v : adj[u]) {
      if (color[v] == -1) {
        if (!dfs(v, c ^ 1)) return false; // Try to color neighbor with opposite color
      } else if (color[v] == c) {
        return false; // Found neighbor with same color → not bipartite
      }
    }
    return true;
  };

  // Run DFS for every unvisited component (handle disconnected graphs)
  for (int i = 1; i <= n; i++) {
    if (color[i] == -1) {
      if (!dfs(i, 0)) return false;
    }
  }

  return true;
}
```

---

## 四、應用場景

* 團隊分組問題（兩隊不能有仇人）
* 二分匹配（如婚姻配對、工作分配）
* 判斷是否存在合法的二著色方案

---

## 五、補充

* Bipartite 圖不一定是樹。
* 所有樹都是 Bipartite，但 Bipartite 不一定是樹。
* 可以用 BFS 實作著色判斷，邏輯類似 DFS。

---

## 六、完整範例程式碼

```cpp
#include <iostream>
#include <vector>
using namespace std;

int n, m;                // n = number of vertices, m = number of edges
vector<vector<int>> adj; // adjacency list of the graph
vector<int> color;       // color[i] = -1 (unvisited), 0 or 1 (two colors)

/**
 * DFS-based bipartite graph checker.
 * Tries to color the graph with two colors (0 and 1),
 * such that no two adjacent vertices have the same color.
 *
 * @param v The current vertex
 * @param c The color to assign to this vertex
 * @return true if the coloring is valid so far, false otherwise
 */
bool isBipartite(int v, int c) {
  color[v] = c;             // Color the current vertex
  for (int node : adj[v]) { // Visit all adjacent vertices
    if (color[node] == -1) {
      // If neighbor not colored yet, recurse with opposite color
      if (!isBipartite(node, c ^ 1))
        return false;
    } else if (color[node] == c) {
      // If neighbor already colored the same as current, not bipartite
      return false;
    }
  }
  return true;
}

int main() {
  cin >> n >> m;
  adj.resize(n + 1); // Resize adjacency list to fit n nodes (1-based index)
  color.assign(n + 1, -1); // Initialize all nodes as unvisited (uncolored)

  // Read all edges and build the adjacency list
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u); // Undirected graph, so add both directions
  }

  // Run DFS for each unvisited component
  for (int i = 1; i <= n; ++i) {
    if (color[i] == -1) {
      if (!isBipartite(i, 0)) {
        cout << "NO\n"; // Graph is not bipartite
        return 0;
      }
    }
  }

  cout << "YES\n"; // Graph is bipartite
  return 0;
}
```

