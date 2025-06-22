# Minimum Spanning Tree (MST) - Competitive Programming Notes

> Kruskal 適合森林（unconnected graph）、稀疏的圖，Prim 則適合連通、稠密的圖。

## Kruskal's Algorithm

### Description

Kruskal's algorithm sorts all edges and adds the smallest edge to the MST, avoiding cycles. Union-Find (Disjoint Set Union - DSU) is used to detect cycles efficiently.

### Code (C++)

```cpp
struct DSU {
  vector<int> parent;
  DSU(int n) : parent(n + 1) {
    iota(parent.begin(), parent.end(), 0);
  }
  int find(int x) {
    if (x != parent[x]) parent[x] = find(parent[x]);
    return parent[x];
  }
  bool unite(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return false;
    parent[fx] = fy;
    return true;
  }
};

int kruskal(int n, vector<tuple<int, int, int>> &edges) {
  DSU dsu(n);
  sort(edges.begin(), edges.end());
  int mst_weight = 0;
  for (auto &[w, u, v] : edges) {
    if (dsu.unite(u, v)) {
      mst_weight += w;
    }
  }
  return mst_weight;
}
```

### Complexity

* Time: O(M log M) due to edge sorting
* Space: O(N) for DSU

---

## Prim's Algorithm

### Description

Prim's algorithm grows the MST by expanding from the closest vertex. A min-heap (priority queue) is used to pick the edge with the minimum weight that connects to the MST.

### Code (C++)

```cpp
int prim(int n, vector<vector<pair<int, int>>> &adj) {
  vector<bool> inMST(n + 1, false);
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
  pq.emplace(0, 1);
  int total = 0;

  while (!pq.empty()) {
    auto [w, u] = pq.top(); pq.pop();
    if (inMST[u]) continue;
    inMST[u] = true;
    total += w;
    for (auto &[v, wt] : adj[u]) {
      if (!inMST[v]) pq.emplace(wt, v);
    }
  }
  return total;
}
```

### Complexity

* Time: O(M log N) using a priority queue
* Space: O(N + M)

---

## Notes

* Both algorithms assume the graph is connected.
* Kruskal is preferred for sparse graphs, Prim is efficient with adjacency lists and dense graphs.
* Remember to zero-index or one-index the graph consistently.

---

## Example Input Format

```
5 6
1 2 3
1 3 4
2 3 1
2 4 2
3 4 5
4 5 7
```

Where the first line is `n m` (number of nodes and edges), followed by `m` lines of `u v w` edges.

