#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pair<int, int>>> graph(n + 1);
  for (int i = 0; i < m; i++) {
    int a, b, w;
    cin >> a >> b >> w;
    graph[a].emplace_back(b, w);
  }

  for (int i = 1; i < n; i++) {
  }
  return 0;
}
