#include <iostream>
#include <queue>
#include <set>
#include <utility>
#include <vector>

using namespace std;

const long long INF = 1e18;
using vvpi = vector<vector<pair<int, int>>>;

long long solve_set(int n, int m, const vvpi &g); // set
long long solve_pq(int n, int m, const vvpi &g);  //  priority_queue

int main() {
  int n, m;
  cin >> n >> m;

  // because node should start from index 1, so declare n + 1 space
  vvpi g(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;      // w is weight between edges
    g[a].emplace_back(b, w); // for directed graph
  }

  cout << solve_pq(n, m, g) << '\n';
  return 0;
}

long long solve_set(int n, int m, const vvpi &g) {
  set<pair<long long, int>> s;
  vector<long long> dist(n + 1, INF);
  dist[1] = 0;
  s.insert({0, 1});

  while (!s.empty()) {
    auto [d, u] = *s.begin();
    s.erase(s.begin());

    for (auto [v, w] : g[u]) {
      if (dist[v] > dist[u] + w) {
        if (dist[v] != INF)
          s.erase({dist[v], v});
        dist[v] = dist[u] + w;
        s.insert({dist[v], v});
      }
    }
  }
  return (dist[n] == INF ? -1 : dist[n]);
}

long long solve_pq(int n, int m, const vvpi &g) {
  // {dist, node}
  priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>>
      pq;
  // dist[node] = distance to the current node
  vector<long long> dist(n + 1, INF);
  dist[1] = 0;
  pq.emplace(0, 1);

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();
    if (d > dist[u])
      continue;

    for (auto [v, w] : g[u]) {
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        pq.emplace(dist[v], v);
      }
    }
  }
  return (dist[n] == INF ? -1 : dist[n]);
}
