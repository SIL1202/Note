#include <iostream>
#include <utility>
#include <vector>
using namespace std;

class US {
private:
  vector<vector<pair<int, int>>> root;
  vector<vector<int>> rank;

public:
  US(int n) {
    root.resize(n, vector<pair<int, int>>(n));
    rank.resize(n, vector<int>(n, 1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        root[i][j] = {i, j}; // 每個座標初始為自己
      }
    }
  }

  pair<int, int> find(int x, int y) {
    if (root[x][y] != make_pair(x, y)) {
      root[x][y] =
          find(root[x][y].first, root[x][y].second); // Path compression
    }
    return root[x][y];
  }

  void Union(pair<int, int> a, pair<int, int> b) {
    auto rootA = find(a.first, a.second);
    auto rootB = find(b.first, b.second);
    if (rootA != rootB) {
      int ax = rootA.first, ay = rootA.second;
      int bx = rootB.first, by = rootB.second;
      if (rank[ax][ay] > rank[bx][by]) {
        root[bx][by] = rootA;
      } else if (rank[ax][ay] < rank[bx][by]) {
        root[ax][ay] = rootB;
      } else {
        root[bx][by] = rootA;
        rank[ax][ay]++;
      }
    }
  }
};

int main() {
  US uf(3); // 建立 3x3 的座標 grid

  // 合併一些座標點
  uf.Union({0, 0}, {0, 1});
  uf.Union({0, 1}, {1, 1});
  uf.Union({2, 2}, {2, 1});

  // 測試哪些點屬於同一集合
  cout << boolalpha;

  // 這三個已合併，所以應該都連通
  cout << (uf.find(0, 0) == uf.find(1, 1)) << endl; // true
  cout << (uf.find(0, 1) == uf.find(1, 1)) << endl; // true

  // 這些沒有合併，應該不連通
  cout << (uf.find(0, 0) == uf.find(2, 2)) << endl; // false
  cout << (uf.find(0, 2) == uf.find(2, 0)) << endl; // false

  // 這兩個有合併
  cout << (uf.find(2, 1) == uf.find(2, 2)) << endl; // true

  return 0;
}
