# Dynamic Programming - Coin Change

## 概念總覽

Coin Change 是一個常見的動態規劃問題，通常會問：

> 有一堆硬幣面額（例如 1 元、5 元、10 元），要怎麼組合出某個金額？

這類問題有兩種常見版本：

- **Coin Combinations I**：計算不同的「排列數」，順序不同算不同。

  For example, if the coins are $\{2,3,5\}$ and the desired sum is $9$, there are $8$ ways:

  - $2+2+5$

  - $2+5+2$

  - $5+2+2$

  - $3+3+3$

  - $2+2+2+3$

  - $2+2+3+2$

  - $2+3+2+2$

  - $3+2+2+2$

    

- **Coin Combinations II**：計算「組合數」，順序無關。

  For example, if the coins are $\{2,3,5\}$ and the desired sum is $9$, there are $3$ ways:

  - $2+2+5$
  - $3+3+3$
  - $2+2+2+3$

### 問題類型分類：

* **Decision problem**：回傳 TRUE / FALSE
* **Counting problem**：回傳總共有幾種解法
* **Optimization problem**：找出最佳解（例如最短、最大、最便宜）

---

## 題型比較：Coin Change 題目的兩種型態

| 題型                 | 是否在意順序    | CSES 對應題目               | 適用場景                               |
| -------------------- | --------------- | --------------------------- | -------------------------------------- |
| Coin Combinations I  | ✅ 有順序 (排列) | ✅ CSES Coin Combinations I  | 順序不同視為不同組合，例如遊戲選擇路徑 |
| Coin Combinations II | ❌ 無順序 (組合) | ✅ CSES Coin Combinations II | 組合方式計算、找零問題                 |

---

## Coin Combinations I（順序有關）

### 狀態定義

* `dp[i]`: 總金額為 `i` 的排列數量（順序有差）

### 一維程式碼

```cpp
int coin_combination_ordered(int x, const vector<int>& coins) {
    vector<int> dp(x + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= x; ++i) {
        for (int c : coins) {
            if (i >= c)
                dp[i] = (dp[i] + dp[i - c]);
        }
    }
    return dp[x];
}
```

### 二維程式碼

```cpp
int coin_combination_ordered_2D(int x, const vector<int>& coins) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
    dp[0][0] = 1;
    for (int k = 1; k <= n; ++k) {
        for (int m = 0; m <= x; ++m) {
            dp[k][m] = dp[k - 1][m];
            if (m >= coins[k - 1])
                dp[k][m] = (dp[k][m] + dp[k][m - coins[k - 1]]);
        }
    }
    return dp[n][x];
}
```

（雖然這版本仍可重複計算順序，但這裡用作對比）

---

## Coin Combinations II（順序無關）

### 狀態定義

* `dp[i]`: 總金額為 `i` 的組合數=量（順序無差）

  > 只需調換迴圈順序就好

### 一維程式碼（標準組合型）

```cpp
int coin_combination_unordered(int x, const vector<int>& coins) {
    vector<int> dp(x + 1, 0);
    dp[0] = 1;
    for (int c : coins) {
        for (int i = c; i <= x; ++i) { // start from c, because if i < c then we can't even use it.
            dp[i] = (dp[i] + dp[i - c]);
        }
    }
    return dp[x];
}
```

### 二維程式碼

```cpp
int coin_combination_unordered_2D(const vector<int>& coins, int x) {
    int n = coins.size();
    vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
    for (int i = 0; i <= n; ++i)
        dp[i][0] = 1;  // base case: amount 0

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= x; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j >= coins[i - 1])
                dp[i][j] = (dp[i][j] + dp[i][j - coins[i - 1]]);
        }
    }
    return dp[n][x];
}
```

