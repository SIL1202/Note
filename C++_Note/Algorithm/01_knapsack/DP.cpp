#include <iostream>
#include <vector>
using namespace std;

void Bottom_up() {
  int n, x;
  cin >> n >> x;
  vector<int> weights(n), values(n);
  vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));

  for (int &w : weights)
    cin >> w;
  for (int &v : values)
    cin >> v;

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= x; j++) {
      if (j >= weights[i - 1]) {
        int pick = values[i - 1] + dp[i - 1][j - weights[i - 1]];
        int skip = dp[i - 1][j];
        dp[i][j] = max(pick, skip);
      } else
        dp[i][j] = dp[i - 1][j];
    }
  }
  cout << dp[n][x] << '\n';
}

void Bottom_up_Optimize() {
  int n, x;
  cin >> n >> x;
  vector<int> weights(n), values(n);
  vector<int> dp(x + 1, 0);

  for (int &w : weights)
    cin >> w;
  for (int &v : values)
    cin >> v;

  for (int i = 0; i < n; i++) {
    for (int j = x; j >= weights[i]; j--) {
      int pick = values[i] + dp[j - weights[i]];
      int skip = dp[j];
      dp[j] = max(pick, skip);
    }
  }
  cout << dp[x] << '\n';
}

void Top_down() { // 前 i 個物品在容量 j 時的最大價值
  int n, x;
  cin >> n >> x;
  vector<int> weights(n), values(n);
  for (int &w : weights)
    cin >> w;
  for (int &v : values)
    cin >> v;

  // memo[i][j], 必須使用二維
  vector<vector<int>> memo(n + 1, vector<int>(x + 1, -1));
  function<int(int, int)> recursive = [&](int i, int j) {
    if (i == 0 || j == 0)
      return 0;
    if (memo[i][j] != -1)
      return memo[i][j];

    int skip = recursive(i - 1, j);
    if (j >= weights[i - 1]) {
      int pick = values[i - 1] + recursive(i - 1, j - weights[i - 1]);
      memo[i][j] = max(pick, skip);
    } else {
      memo[i][j] = skip;
    }
    return memo[i][j];
  };

  cout << recursive(n, x) << '\n';
}

int main() {
  Bottom_up();
  Bottom_up_Optimize();
  Top_down();
  return 0;
}
