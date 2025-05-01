#include <list>
#include <queue>
#include <vector>

typedef int WeightType;
struct Edge {
  int u, v;
  WeightType w;
};

struct Graph {
  Graph(int n) : E(n) {}
  std::vector<std::list<Edge>> E;
  void add_edge(int u, int v, WeightType w) {
    E[u].push_back({u, v, w});
    E[v].push_back({v, u, w});
  }
  int n() const { return E.size(); }
};

std::pair<Graph, int> MSF(const Graph &G) {
  auto WeightComp = [](const Edge &e1, const Edge &e2) { return e1.w > e2.w; };
  std::priority_queue<Edge, std::vector<Edge>, decltype(WeightComp)> candidates(
      WeightComp);

  Graph forest(G.n()); // 儲存生成森林
  std::vector<bool> visited(G.n(), false);
  int tree_count = 0; // 統計森林數量

  for (int start = 0; start < G.n(); ++start) {
    if (!visited[start]) { // 發現新的聯通組件
      tree_count++;
      visited[start] = true;
      // 將起始頂點的鄰接邊加入隊列
      for (const Edge &e : G.E[start]) {
        if (!visited[e.v])
          candidates.push(e);
      }

      // Prim 算法擴展當前生成樹
      while (!candidates.empty()) {
        Edge safe = candidates.top();
        candidates.pop();
        int u = visited[safe.v] ? safe.u : safe.v; // 確定未訪問頂點
        if (!visited[u]) {
          visited[u] = true;
          forest.add_edge(safe.u, safe.v, safe.w); // 加入生成森林

          // 將u的鄰接邊加入隊列
          for (const Edge &e : G.E[u]) {
            if (!visited[e.v])
              candidates.push(e);
          }
        }
      }
    }
  }
  return {forest, tree_count};
}
