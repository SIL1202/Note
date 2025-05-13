#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
public:
  UnionFind(int sz) : root(sz), rank(sz) {
    for (int i = 0; i < sz; i++) {
      root[i] = i;
      rank[i] = 1;
    }
  }

  // Path Compression
  int find(int x) {
    if (root[x] == x)
      return x;
    return root[x] = find(root[x]);
  }

  // Rank 避免樹成一條線的最壞情況
  void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
      if (rank[rootX] > rank[rootY])
        root[rootY] = rootX;
      else if (rank[rootX] < rank[rootY])
        root[rootX] = rootY;
      else {
        root[rootY] = rootX;
        rank[rootX]++;
      }
    }
  }

  bool connected(int x, int y) { return find(x) == find(y); }

private:
  vector<int> root;
  vector<int> rank;
};

// Test Case
int main() {
  // for displaying booleans as literal strings, instead of 0 and 1
  cout << boolalpha;
  UnionFind uf(10);
  // 1-2-5-6-7 3-8-9 4
  uf.unionSet(1, 2);
  uf.unionSet(2, 5);
  uf.unionSet(5, 6);
  uf.unionSet(6, 7);
  uf.unionSet(3, 8);
  uf.unionSet(8, 9);
  cout << uf.connected(1, 5) << endl; // true
  cout << uf.connected(5, 7) << endl; // true
  cout << uf.connected(4, 9) << endl; // false
  // 1-2-5-6-7 3-8-9-4
  uf.unionSet(9, 4);
  cout << uf.connected(4, 9) << endl; // true

  return 0;
}
