#include <iostream>
#include <vector>
using namespace std;

int n, m;                // n = number of vertices, m = number of edges
vector<vector<int>> adj; // adjacency list of the graph
vector<int> color;       // color[i] = -1 (unvisited), 0 or 1 (two colors)

/**
 * DFS-based bipartite graph checker.
 * Tries to color the graph with two colors (0 and 1),
 * such that no two adjacent vertices have the same color.
 *
 * @param v The current vertex
 * @param c The color to assign to this vertex
 * @return true if the coloring is valid so far, false otherwise
 */
bool isBipartite(int v, int c) {
  color[v] = c;             // Color the current vertex
  for (int node : adj[v]) { // Visit all adjacent vertices
    if (color[node] == -1) {
      // If neighbor not colored yet, recurse with opposite color
      if (!isBipartite(node, c ^ 1))
        return false;
    } else if (color[node] == c) {
      // If neighbor already colored the same as current, not bipartite
      return false;
    }
  }
  return true;
}

int main() {
  cin >> n >> m;
  adj.resize(n + 1); // Resize adjacency list to fit n nodes (1-based index)
  color.assign(n + 1, -1); // Initialize all nodes as unvisited (uncolored)

  // Read all edges and build the adjacency list
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u); // Undirected graph, so add both directions
  }

  // Run DFS for each unvisited component
  for (int i = 1; i <= n; ++i) {
    if (color[i] == -1) {
      if (!isBipartite(i, 0)) {
        cout << "NO\n"; // Graph is not bipartite
        return 0;
      }
    }
  }

  cout << "YES\n"; // Graph is bipartite
  return 0;
}
