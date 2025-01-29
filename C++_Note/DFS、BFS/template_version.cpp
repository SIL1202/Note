#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

template <typename T> class Graph {
public:
  // Add an undirected edge between two vertices
  void addEdge(const T &u, const T &v) {
    // If 'u' or 'v' does not exist in adjacency, they will be created
    // automatically
    adjacency[u].push_back(v);
    adjacency[v].push_back(u);
  }

  // Print BFS traversal from a starting vertex 'start'
  void BFS(const T &start) {
    // If start vertex not in graph, do nothing or throw
    if (adjacency.find(start) == adjacency.end()) {
      std::cerr << "BFS: Start vertex not in graph.\n";
      return;
    }

    // Keep track of visited vertices
    std::unordered_map<T, bool> visited;
    for (auto &pair : adjacency) {
      visited[pair.first] = false;
    }

    std::queue<T> q;
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
      T current = q.front();
      q.pop();
      std::cout << current << " ";

      // Explore neighbors
      for (auto &neighbor : adjacency[current]) {
        if (!visited[neighbor]) {
          visited[neighbor] = true;
          q.push(neighbor);
        }
      }
    }
    std::cout << std::endl;
  }

  // Print DFS traversal from a starting vertex 'start'
  // (wrapper function: sets up visited map, calls a recursive helper)
  void DFS(const T &start) {
    if (adjacency.find(start) == adjacency.end()) {
      std::cerr << "DFS: Start vertex not in graph.\n";
      return;
    }

    // Initialize visited map
    std::unordered_map<T, bool> visited;
    for (auto &pair : adjacency) {
      visited[pair.first] = false;
    }

    // Call the recursive helper
    dfsHelper(start, visited);
    std::cout << std::endl;
  }

private:
  // The adjacency list, mapping a vertex T to a list of T neighbors
  std::unordered_map<T, std::vector<T>> adjacency;

  // Recursive DFS helper
  void dfsHelper(const T &current, std::unordered_map<T, bool> &visited) {
    visited[current] = true;
    std::cout << current << " ";

    // Recurse on each unvisited neighbor
    for (auto &neighbor : adjacency[current]) {
      if (!visited[neighbor]) {
        dfsHelper(neighbor, visited);
      }
    }
  }
};

int main() {
  // Create a Graph of type 'char'
  Graph<char> g;

  // Add undirected edges between some chars
  g.addEdge('A', 'B');
  g.addEdge('A', 'C');
  g.addEdge('B', 'D');
  g.addEdge('C', 'E');
  g.addEdge('D', 'E'); // You can add as many edges as you like

  std::cout << "BFS from 'A':\n";
  g.BFS('A'); // e.g. might print A B D E C, depending on adjacency ordering

  std::cout << "DFS from 'A':\n";
  g.DFS('A'); // e.g. might print A B D E C, or some other valid DFS path

  return 0;
}
