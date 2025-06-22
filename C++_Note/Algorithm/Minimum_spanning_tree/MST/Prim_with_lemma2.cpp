#include <iostream>
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

  void add_Edge(int u, int v, WeightType w) {
    E[u].push_back({u, v, w});
    E[v].push_back({v, u, w});
  }
  int n() const { return E.size(); }
  int m() const {
    int res = 0;

    for (auto list : E)
      res += list.size();
    return res / 2;
  }
};

Graph MST(const Graph &G) {
  auto WeightComp = [](const Edge e1, const Edge e2) { return e1.w > e2.w; };
  std::priority_queue<Edge, std::vector<Edge>, decltype(WeightComp)> candidates(
      WeightComp);
  // Step 1
  Graph T(G.n());
  std::vector<bool> visited(G.n(), false);
  visited[0] = true;

  // maintain candidates
  // 邏輯：
  // 检查边的起点 e.u 是否是 0：
  // 如果是（e.u == 0），说明邻居是 e.v。
  // 如果不是（e.u != 0），说明邻居是 e.u（因为无向图中 e.v 必然是 0）。
  //
  // 示例：
  // 若 e = (0,3,2)，则 e.u == 0 为真，v = e.v = 3。
  // 若 e = (3,0,2)，则 e.u == 0 为假，v = e.u = 3。
  for (Edge e : G.E[0]) {
    int v = (e.u == 0) ? e.v : e.u;
    if (!visited[v])
      candidates.push(e);
  }

  while (true) {
    while (!candidates.empty()) {
      Edge temp = candidates.top(); // 查看堆頂邊 （當前權重的候選邊)
      // Lemma 2/ remove useless edges from candidates
      // 檢查兩個頂點是否都已被訪問過
      if (visited[temp.u] && visited[temp.v]) {
        candidates.pop(); // 如果是無效邊，丟棄他
      } else
        break;
    }
    // if no more safe edges, end up the algorithm
    if (candidates.empty())
      break;
    // Step 2: 取出當前最小權重的安全邊
    Edge safe = candidates.top();
    candidates.pop();

    // Step 3: 確定新加入生成樹的頂點
    int u = visited[safe.v] ? safe.u : safe.v;
    visited[u] = true;

    // 將安全邊加入生成樹
    T.add_Edge(safe.u, safe.v, safe.w);

    // 維護候選邊: 將新頂點u 的臨接邊加入隊列
    for (Edge e : G.E[u]) {
      if (!visited[e.v]) {
        candidates.push(e);
      }
    }
  }
  return T;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  Graph g(n);
  g.add_Edge(1, 2, 7);
  g.add_Edge(1, 4, 6);
  g.add_Edge(4, 2, 9);
  g.add_Edge(4, 3, 8);
  g.add_Edge(2, 3, 6);

  Graph A = MST(g);
  int weight = 0;
  for (std::list<Edge> &w : A.E) {
    weight += w.back().w;
  }
  return 0;
}
