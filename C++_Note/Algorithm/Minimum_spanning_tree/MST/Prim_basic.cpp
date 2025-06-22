#include <functional>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> adj(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
  vector<bool> visited(n + 1, false);

  int total = 0;
  pq.emplace(0, 1); // 起點設為 1，權重為 0

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (visited[u])
      continue;
    visited[u] = true; //  只有真正被選進 MST 時才設為 true
    total += d;

    for (const auto &[v, w] : adj[u]) {
      if (!visited[v]) {
        pq.emplace(w, v); // 只放進候選清單，不設 visited
      }
    }
  }

  cout << "total = " << total << '\n';
  return 0;
}
