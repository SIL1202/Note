# 🎒 背包問題總整理（Knapsack Variants）

本篇整理常見背包問題，著重在：
- 狀態轉移方程式
- DP 陣列定義
- 演算法是否屬於 P / NP / NP-hard
- 補上完整程式迴圈範例（用 C++ 為主）

---

## 🟠 1. 0/1 Knapsack Problem

- **DP 陣列定義**：`dp[i][w]` 表示在前 `i` 個物品中，容量為 `w` 時的最大價值。
- **狀態轉移方程**：
  ```cpp
  for (int i = 1; i <= n; ++i) {
      for (int w = 0; w <= W; ++w) {
          if (w >= weight[i])
              dp[i][w] = max(dp[i-1][w], dp[i-1][w - weight[i]] + value[i]);
          else
              dp[i][w] = dp[i-1][w];
      }
  }
  ```
- **時間複雜度**：`O(nW)`（W 為容量）
- **屬於**：NP（pseudo-polynomial 解，尚未證明是否屬於 P）

---

## 🟠 2. Unbounded Knapsack Problem

- **DP 陣列定義**：`dp[w]` 表示容量為 `w` 時的最大總價值，物品可重複選擇。
- **狀態轉移方程**：
  ```cpp
  for (int i = 1; i <= n; ++i) {
      for (int w = weight[i]; w <= W; ++w) {
          dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
      }
  }
  ```
- **時間複雜度**：`O(nW)`
- **屬於**：NP（pseudo-polynomial）

---

## 🟢 3. Fractional Knapsack Problem（可切割）

- **解法**：使用貪婪演算法，依照價值密度排序後裝填。
- **時間複雜度**：`O(n log n)`（排序）
- **程式碼概念**：
  ```cpp
  sort(items.begin(), items.end(), [](auto& a, auto& b) {
      return a.value / a.weight > b.value / b.weight;
  });
  for (auto& item : items) {
      if (capacity >= item.weight) {
          total += item.value;
          capacity -= item.weight;
      } else {
          total += item.value * (capacity / item.weight);
          break;
      }
  }
  ```
- **屬於**：P 

---

## 🔴 4. Multi-dimensional Knapsack Problem（多維背包）

- **DP 陣列定義**：`dp[i][w][v]` 表示前 `i` 個物品在重量 ≤ `w`、體積 ≤ `v` 下的最大價值。
- **狀態轉移方程**：
  ```cpp
  for (int i = 1; i <= n; ++i)
      for (int w = 0; w <= W; ++w)
          for (int v = 0; v <= V; ++v)
              if (w >= weight[i] && v >= volume[i])
                  dp[i][w][v] = max(dp[i-1][w][v], dp[i-1][w - weight[i]][v - volume[i]] + value[i]);
              else
                  dp[i][w][v] = dp[i-1][w][v];
  ```
- **時間複雜度**：`O(nWV)`
- **屬於**：NP-hard 

---

## 🔴 5. Multiple Knapsack Problem（多背包）

- **描述**：多個背包（各自容量），物品需分配進某個背包，不可重複。
- **常見作法**：狀態 `dp[i][c1][c2]` 或用 bitmask + dfs/bfs
- **屬於**：NP-complete

---

## 🔴 6. Knapsack Decision Problem

- **描述**：是否存在一組物品，使得總重量 ≤ W 且總價值 ≥ K？
- **轉移與判斷式**：
  ```cpp
  for (int i = 1; i <= n; ++i)
      for (int w = 0; w <= W; ++w)
          if (w >= weight[i])
              dp[i][w] = max(dp[i-1][w], dp[i-1][w - weight[i]] + value[i]);
          else
              dp[i][w] = dp[i-1][w];
  
  // 判斷是否存在某個 w 使得 dp[n][w] >= K
  ```
- **屬於**：NP 

---

## 🔴 7. Generalized Assignment Problem（分配型背包問題）

- **描述**：有 `n` 個物品與 `m` 個背包，每個背包有自己的容量限制。 每個物品只能被分配給其中一個背包。若物品 `i` 被分配給背包 `j`：

  每個背包 `j` 的總使用容量不得超過 `capacity[j]`

- **方法一**：$dp[i][c1][c2]...[cm] =$ 前 $i$ 個物品在各背包容量 $c1$ ~ $cm$下的最大總價值

- **方法二**：使用 Bitmask DP 確保物品只被分配一次

  - `mask` 是一個 n 位二進位數，表示哪些物品已被分配
  - `j` 是目前處理的背包編號
  - `w` 是這個背包的使用容量

  ```cpp
  dp[mask][j][w] = 當前物品分配狀態為 mask，背包 j 使用 w 容量的最大總價值
  ```

  ```cpp
  int n, m; // 物品數，背包數
  vector<vector<int>> cost(n, vector<int>(m));
  vector<vector<int>> value(n, vector<int>(m));
  vector<int> capacity(m);
  int maxMask = 1 << n;
  vector<vector<vector<int>>> dp(maxMask, vector<vector<int>>(m, vector<int>(101, -1)));
  // 初始狀態
  dp[0][0][0] = 0;
  
  for (int mask = 0; mask < maxMask; ++mask) {
      for (int j = 0; j < m; ++j) {
          for (int w = 0; w <= capacity[j]; ++w) {
              if (dp[mask][j][w] == -1) continue;
              for (int i = 0; i < n; ++i) {
                  if ((mask >> i) & 1) continue; // 已被分配
                  int newW = w + cost[i][j];
                  if (newW > capacity[j]) continue;
                  int newMask = mask | (1 << i);
                  dp[newMask][j][newW] = max(dp[newMask][j][newW], dp[mask][j][w] + value[i][j]);
              }
              // 也可以考慮轉到下一個背包（不放東西）
              if (j + 1 < m)
                  dp[mask][j + 1][0] = max(dp[mask][j + 1][0], dp[mask][j][w]);
          }
      }
  }
  // 找最大值
  int ans = 0;
  for (int j = 0; j < m; ++j)
      for (int w = 0; w <= capacity[j]; ++w)
          ans = max(ans, dp[maxMask - 1][j][w]);
  cout << "最大總價值: " << ans << endl;
  ```

- **狀態定義**：$dp[mask][j][c]$ 或 $dp[i][c1][c2]...$

  | 項目       | 說明                      |
  | ---------- | ------------------------- |
  | 時間複雜度 | $O(2ⁿ × m × C)$             |
  | 空間複雜度 | $O(2ⁿ × m × C)$           |
  | 類別       | NP-hard ❌（困難度非常高） |

---

## 🔴 8. 最大價值對應最小重量（Min-Weight for Max-Value）

- **描述**：在所有最大總價值的選法中，找出所需總重量「最小」的方案。
- **DP 陣列定義**：`dp[v]` 表示達成總價值 `v` 所需的最小重量。
- **狀態轉移方程**：
  
  ```cpp
  vector<int> dp(V+1, INF);
  dp[0] = 0;
  for (int i = 1; i <= n; ++i)
      for (int v = V; v >= value[i]; --v)
          dp[v] = min(dp[v], dp[v - value[i]] + weight[i]);
  
  // 最終答案為最大的 v，使得 dp[v] <= W
  ```
- **時間複雜度**：`O(nV)`
- **屬於**：NP 

---

## ✅ 總表對照：

| 問題類型                           | 狀態轉移 / 解法               | 複雜度類別    |
| ---------------------------------- | ----------------------------- | ------------- |
| 0/1 Knapsack                       | `dp[i][w]`                    | NP            |
| Unbounded Knapsack                 | `dp[w]`                       | NP            |
| Fractional Knapsack                | 貪婪法                        | P ✅           |
| Multi-dimensional Knapsack         | `dp[i][w][v]`                 | NP-hard ❌     |
| Multiple Knapsack                  | 多重狀態 + 分配               | NP-complete ❌ |
| Knapsack Decision                  | `dp[i][w] ≥ K` 判斷           | NP ✅          |
| Generalized Assignment (GAP)       | `dp[mask][j][w]` / assignment | NP-hard ❌     |
| Min-Weight for Max-Value（你這題） | `dp[v]`（以價值為主）         | NP ✅          |