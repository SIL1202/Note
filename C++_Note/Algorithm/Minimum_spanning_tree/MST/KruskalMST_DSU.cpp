// Kurskal's algorithm using Disjoint set
#include <list>
#include <vector>

typedef int WeightType;

struct Edge {
  int u, v;
  WeightType w;
  Edge(int u, int v, WeightType w) : u(u), v(v), w(w) {}
};

struct Graph {
  int V;
  std::vector<std::list<Edge>> adj;

  Graph(int V) : V(V), adj(V) {}

  void addEdge(int u, int v, WeightType w) {
    adj[u].push_back(Edge(u, v, w));
    adj[v].push_back(Edge(v, u, w));
  }
};

class DSU {
private:
  std::vector<int> parent;
  std::vector<int> rank;

public:
  DSU(int n) : parent(n), rank(n, 0) {
    for (int i = 0; i < n; ++i) {
      parent[i] = i;
    }
  }

  int Find(int u) {
    if (parent[u] != u) {
      parent[u] = Find(parent[u]);
    }
    return parent[u];
  }

  bool Union(int u, int v) {
    int rootU = Find(u);
    int rootV = Find(v);
    if (rootU == rootV) {
      return false;
    }

    if (rank[rootU] > rank[rootV]) {
      parent[rootV] = rootU;
    } else if (rank[rootU] < rank[rootV]) {
      parent[rootU] = rootV;
    } else {
      parent[rootV] = rootU;
      rank[rootU]++;
    }
    return true;
  }
};

bool isUselessEdge(DSU &dsu, const Edge &e) {
  return dsu.Find(e.u) == dsu.Find(e.v);
}
// sorting edge O(ElogE)
// Find, union O(𝛼(V))
// O(ElogE) or O(ElogV) ，because logE <= 2logV

Graph KruskalMST(const Graph &G) {
  std::vector<Edge> edges;

  for (int u = 0; u < G.V; ++u) {
    for (const Edge &e : G.adj[u]) {
      if (e.u < e.v) {
        edges.push_back(e);
      }
    }
  }

  std::sort(edges.begin(), edges.end(),
            [](const Edge &a, const Edge &b) { return a.w < b.w; });

  DSU dsu(G.V);
  Graph MST(G.V);
  for (const Edge &e : edges) {
    if (!isUselessEdge(dsu, e)) {
      dsu.Union(e.u, e.v);
      MST.addEdge(e.u, e.v, e.w);
    }
  }

  return MST;
}
