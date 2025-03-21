#include <iostream>
#include <vector>

void DFS(int, std::vector<std::vector<int>> &, std::vector<bool> &);
int main() {
  std::vector<std::vector<int>> graph = {
      {1, 2},    // node 0
      {0, 3, 4}, // node 1
      {0},       // node 2
      {1},       // node 3
      {1}        // node 4
  };
  int n = 5;
  std::vector<bool> visited(n, false);
  int start = 0;
  DFS(start, graph, visited);
  return 0;
}

void DFS(int node, std::vector<std::vector<int>> &graph,
         std::vector<bool> &visited) {
  std::cout << node << " ";
  visited[node] = true;

  for (int &neighbor : graph[node]) {
    if (!visited[neighbor])
      DFS(neighbor, graph, visited);
  }
}
