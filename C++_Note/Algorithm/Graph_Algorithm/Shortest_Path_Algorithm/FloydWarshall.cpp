#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
using ll = long long;
const ll INF = 1e18;
using vvpi = vector<vector<pair<int, int>>>;

int main() {
  int n, m;
  cin >> n >> m;

  vvpi g(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    g[a].emplace_back(b, w);
    g[b].emplace_back(a, w); // 若是雙向圖
  }

  vector<vector<ll>> dist(n + 1, vector<ll>(n + 1, INF));
  for (int i = 1; i <= n; i++)
    dist[i][i] = 0;

  for (int u = 1; u <= n; u++) {
    for (auto [v, w] : g[u]) {
      dist[u][v] = min(dist[u][v], (ll)w);
    }
  }

  for (int k = 1; k <= n; k++)
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

  return 0;
}
