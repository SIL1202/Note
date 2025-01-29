#include <iostream>
#include <queue>

class Graph {
private:
  int n;
  std::vector<std::vector<int>> adj;

public:
  Graph(int n) {
    this->n = n;
    adj.resize(n);
  }

  void addEdge(int u, int v) {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  void BFS(int start) {
    std::vector<bool> visited(n, false);

    std::queue<int> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
      int current = q.front();
      q.pop();
      std::cout << current << " ";

      for (int neighbor : adj[current]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }
    }
    std::cout << std::endl;
  }

  void DFS(int start) {
    std::vector<bool> visited(n, false);

    dfsRecursive(start, visited);
    std::cout << std::endl;
  }

private:
  void dfsRecursive(int current, std::vector<bool> &visited) {
    visited[current] = true;
    std::cout << current << " ";

    for (int neighbor : adj[current]) {
      if (!visited[neighbor]) {
        dfsRecursive(neighbor, visited);
      }
    }
  }
};

int main() {
  Graph graph(5);
  graph.addEdge(0, 1);
  graph.addEdge(0, 2);
  graph.addEdge(1, 3);
  graph.addEdge(2, 3);
  graph.addEdge(3, 4);

  graph.DFS(0);
  graph.BFS(0);

  return 0;
}
