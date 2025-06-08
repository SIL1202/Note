// 🎒 背包問題總整理
// 包含：問題定義、狀態轉移方程、完整程式架構（C++），以及該問題是否屬於 P

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// 🟠 1. 0/1 Knapsack Problem
// dp[i][w]：表示前 i 個物品中，在容量為 w 時可達到的最大價值
// 狀態轉移：dp[i][w] = max(dp[i-1][w], dp[i-1][w-weight[i]] + value[i])
// 時間複雜度：O(nW) → pseudo-polynomial
// 屬於：NP（但目前無證明是否屬於 P）
int zeroOneKnapsack(int W, const vector<int> &weight,
                    const vector<int> &value) {
  int n = weight.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= W; ++w) {
      if (w >= weight[i - 1])
        dp[i][w] =
            max(dp[i - 1][w], dp[i - 1][w - weight[i - 1]] + value[i - 1]);
      else
        dp[i][w] = dp[i - 1][w];
    }
  }
  return dp[n][W];
}

// 🟠 2. Unbounded Knapsack Problem
// dp[w]：在容量為 w 時可達到的最大價值（每個物品可無限次使用）
// 狀態轉移：dp[w] = max(dp[w], dp[w - weight[i]] + value[i])
// 時間複雜度：O(nW) → pseudo-polynomial
// 屬於：NP
int unboundedKnapsack(int W, const vector<int> &weight,
                      const vector<int> &value) {
  int n = weight.size();
  vector<int> dp(W + 1, 0);
  for (int i = 0; i < n; ++i) {
    for (int w = weight[i]; w <= W; ++w) {
      dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
    }
  }
  return dp[W];
}

// 🟢 3. Fractional Knapsack Problem（用貪婪）
// 時間複雜度：O(n log n)
// 屬於：P
struct Item {
  int weight, value;
  double ratio() const { return (double)value / weight; }
};
bool cmp(Item a, Item b) { return a.ratio() > b.ratio(); }
double fractionalKnapsack(int W, vector<Item> &items) {
  sort(items.begin(), items.end(), cmp);
  double total = 0;
  for (auto &item : items) {
    if (W >= item.weight) {
      W -= item.weight;
      total += item.value;
    } else {
      total += item.ratio() * W;
      break;
    }
  }
  return total;
}

// 🔴 4. Multi-dimensional Knapsack Problem
// dp[i][w][v]：表示前 i 個物品在重量限制 w、體積限制 v 下的最大價值
// 狀態轉移：dp[i][w][v] = max(dp[i-1][w][v], dp[i-1][w - weight[i]][v -
// volume[i]] + value[i]) 屬於：NP-hard
int multiDimensionalKnapsack(int W, int V, const vector<int> &weight,
                             const vector<int> &volume,
                             const vector<int> &value) {
  int n = weight.size();
  vector<vector<vector<int>>> dp(
      n + 1, vector<vector<int>>(W + 1, vector<int>(V + 1, 0)));
  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= W; ++w) {
      for (int v = 0; v <= V; ++v) {
        if (w >= weight[i - 1] && v >= volume[i - 1])
          dp[i][w][v] = max(dp[i - 1][w][v],
                            dp[i - 1][w - weight[i - 1]][v - volume[i - 1]] +
                                value[i - 1]);
        else
          dp[i][w][v] = dp[i - 1][w][v];
      }
    }
  }
  return dp[n][W][V];
}

// 🔴 5. Multiple Knapsack Problem（多背包）
// 狀態會變成 dp[i][j][k]... 每個背包一個維度 → 狀態空間爆炸，通常用 bitmask
// 優化 屬於：NP-complete

// 🔴 6. Knapsack Decision Problem
// dp[i][w]：前 i 個物品，在總重量 ≤ w 下，是否可達到總價值 ≥ K
// 判斷是否存在這樣的選法
// 屬於：NP
bool knapsackDecision(int W, int K, const vector<int> &weight,
                      const vector<int> &value) {
  int n = weight.size();
  vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= W; ++w) {
      if (w >= weight[i - 1])
        dp[i][w] =
            max(dp[i - 1][w], dp[i - 1][w - weight[i - 1]] + value[i - 1]);
      else
        dp[i][w] = dp[i - 1][w];
    }
  }
  for (int w = 0; w <= W; ++w) {
    if (dp[n][w] >= K)
      return true;
  }
  return false;
}

int main() {
  // 範例資料可自行測試
  vector<int> weight = {2, 3, 4, 5};
  vector<int> value = {3, 4, 5, 6};
  int W = 5;
  cout << "0/1 Knapsack: " << zeroOneKnapsack(W, weight, value) << endl;
  cout << "Unbounded Knapsack: " << unboundedKnapsack(W, weight, value) << endl;

  vector<Item> items = {{2, 3}, {3, 4}, {4, 5}, {5, 6}};
  cout << "Fractional Knapsack: " << fractionalKnapsack(W, items) << endl;

  vector<int> volume = {1, 2, 3, 4};
  int V = 5;
  cout << "Multi-dimensional Knapsack: "
       << multiDimensionalKnapsack(W, V, weight, volume, value) << endl;

  cout << "Knapsack Decision (K=7): "
       << (knapsackDecision(W, 7, weight, value) ? "YES" : "NO") << endl;
  return 0;
}
