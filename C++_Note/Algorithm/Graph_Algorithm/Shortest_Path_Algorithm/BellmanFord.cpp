#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

#define ll long long
using Node = tuple<int, int, int>; // from, to, weight
const ll INF = 1e18;

int main() {
  int n, m;
  cin >> n >> m;
  vector<Node> edges;

  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    edges.emplace_back(a, b, w);
  }

  vector<ll> dist(n + 1, INF);
  dist[1] = 0; // suppose it start from 1

  for (int i = 1; i <= n - 1; i++) {
    for (const auto &[u, v, w] : edges) {
      if (dist[u] != INF && dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
      }
    }
  }

  bool hasNegativeEdge = false;
  for (const auto &[u, v, w] : edges) {
    if (dist[u] != INF && dist[v] > dist[u] + w) {
      hasNegativeEdge = true;
      break;
    }
  }

  if (hasNegativeEdge)
    cout << "Negative edge detected!\n";
  else
    for (int i = 1; i <= n; i++)
      cout << (dist[i] == INF ? -1 : dist[i]) << '\n';

  return 0;
}
