#include <iostream>
#include <vector>
using namespace std;

#define pb push_back
const int MAX = 2e5 + 5;
int n;
vector<int> adj[MAX];
vector<int> vis;
int maxD, maxNode;

void dfs(int v, int d) {
  vis[v] = true;
  if (d > maxD)
    maxD = d, maxNode = v;
  for (int u : adj[v]) {
    if (!vis[u]) {
      dfs(u, d + 1);
    }
  }
};

int main() {
  cin >> n;
  int a, b;
  vis.assign(n + 1, false);
  for (int i = 0; i < n - 1; i++)
    cin >> a >> b, adj[a].pb(b), adj[b].pb(a);

  maxD = -1;
  dfs(1, 0);

  vis.assign(n + 1, false);
  maxD = -1;
  dfs(maxNode, 0);

  cout << maxD << '\n';
}
