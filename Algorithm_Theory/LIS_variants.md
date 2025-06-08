# 📈 最長遞增子序列問題總整理（Longest Increasing Subsequence, LIS）

本篇整理 LIS 與 LCS 相關問題，著重在：
- 狀態轉移方程式與 DP 陣列定義
- 演算法是否屬於 P / NP / NP-hard 並附上簡要原因

---

## 🟢 1. 經典 LIS 問題

- **定義**：找出一個數列中，最長的遞增子序列（不要求連續）
- **DP 陣列**：$dp[i] =$ 以第 $i$ 個元素結尾的 LIS 長度
- **轉移方程**：
  
  ```cpp
  dp[i] = max(dp[j] + 1), for all j < i 且 nums[j] < nums[i]
  ```
- **複雜度**：$O(n²)$
- **分類**：P ✅（演算法可在多項式時間內解出答案）

---

## 🟢 2. 二分優化 LIS

- **tails[k] = 長度為 k+1 的遞增子序列的最小結尾值**

- 使用 `lower_bound()` 找插入位置

  ```cpp
  int lengthOfLIS(vector<int>& nums) {
      vector<int> tails; // tails[i] = 長度為 i+1 的 LIS 結尾的最小值
      for (int x : nums) {
          auto it = lower_bound(tails.begin(), tails.end(), x);
          if (it == tails.end()) {
              tails.push_back(x);  // 長度變長
          } else {
              *it = x; // 更新尾巴為更小的值
          }
      }
      return tails.size();
  }
  ```

- **複雜度**：$O(n log n)$

- **分類**：P ✅（貪婪 + 二分法都是多項式可解）

---

## 🔁 3. Longest Non-Decreasing Subsequence (LNDS)

- 修改判斷條件為 `≤` 即可
- **複雜度**：$O(n²)$
- **分類**：P ✅（與 LIS 同）

---

## 🔢 4. Longest Decreasing Subsequence (LDS)

- 題目與 LIS 類似，只是改成遞減，可透過反轉處理
- **分類**：P ✅

---

## 🎯 5. LIS 條數 / 方案數

- 在經典 LIS 的基礎上額外加一個 $`count[]`$
- 統計有幾種不同方案能達成該長度
- **分類**：P ✅（雖多一維度，但仍為多項式時間內可完成）

---

## 🔁 6. LIS 長度固定的最小字典序解

> 給定一個整數陣列 nums 和一個整數 K，找出所有長度為 K 的 LIS 中，**字典序最小**的那一條。

- 結合單調棧、貪婪選擇與逆推技巧

  ```cpp
  vector<int> smallestLISofLengthK(vector<int>& nums, int K) {
      int n = nums.size();
      vector<int> dp(n, 1);
      // Step 1: 從右往左計算 dp[i] 表示從 i 開始的 LIS 最長長度
      for (int i = n - 2; i >= 0; --i) {
          for (int j = i + 1; j < n; ++j) {
              if (nums[i] < nums[j]) {
                  dp[i] = max(dp[i], 1 + dp[j]);
              }
          }
      }
      vector<int> result;
      int prev = -1; // 初始沒有選數字
      int idx = 0;
  
      for (int len = K; len > 0; --len) {
          int minVal = INT_MAX;
          int minPos = -1;
  
          // 從目前位置往後找「可選擇的最小值」
          for (int i = idx; i < n; ++i) {
              if ((result.empty() || nums[i] > result.back()) &&
                  dp[i] >= len &&
                  nums[i] < minVal) {
                  minVal = nums[i];
                  minPos = i;
              }
          }
          result.push_back(minVal);
          idx = minPos + 1; // 下一輪從 minPos 後面開始
      }
      return result;
  }
  ```

  

- **分類**：P ✅（邏輯進階但仍是明確演算法）

---

## 🔁 7. Online LIS / 動態更新 LIS

> 資料是一個一個「動態輸入」的，我們希望在每次輸入一個數字後，**即時回報目前的 LIS 長度**。

```cpp
void processOnlineLIS(const vector<int>& stream) {
    vector<int> tails;

    for (int x : stream) {
        auto it = lower_bound(tails.begin(), tails.end(), x);
        if (it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
        cout << "輸入 " << x << " → 當前 LIS 長度 = " << tails.size() << endl;
    }
}
```

- 用 BIT、Segment Tree 實作 tails 儲存並實時查詢與更新
- **分類**：P ✅（資料結構操作皆可在 log 時間完成）

---

## 🔴 8. 回溯 LIS 路徑

- 額外加上 $`prev[i]`$ 陣列來紀錄路徑來源，從尾端反推回去
- **分類**：P ✅（雖有重建過程，但仍屬於多項式時間）

---

## 🔵 9. 最長共同子序列（Longest Common Subsequence, LCS）

- **定義**：給定兩個字串 A, B，找出最長公共子序列

- **DP 陣列**：$dp[i][j] = A[0..i-1]$ 與 $B[0..j-1]$ 的 LCS 長度

  > $dp[i][j]$ 表示「A 的前 i 個字元」和「B 的前 j 個字元」之間，能夠湊出多長的 LCS

- **轉移方程**：
  
  ```cpp
  for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= m; ++j)
              if (A[i - 1] == B[j - 1])
                  dp[i][j] = dp[i - 1][j - 1] + 1;
              else
                  dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
  ```
  
- **複雜度**：$O(n × m)$

- **分類**：P ✅（可透過動態規劃在合理時間內完成）

---

## 🔵 10. 回溯 LCS 路徑

- 類似 LIS 回溯，加一個 $`prev[i][j]`$ 追蹤來源方向
- **分類**：P ✅

---

## 🔵 11. LCS 在三個字串上（3-LCS）

> 給定三個字串 A、B、C，找出三個字串共同的 **最長遞增子序列**（不一定連續）的長度。

- 將 dp 擴展成三維：$dp[i][j][k] = A$ 的前 $i$ 個、$B$ 的前 $j$ 個、$C$ 的前 $k$ 個字元的 LCS 長度

  ```cpp
  if (A[i-1] == B[j-1] && B[j-1] == C[k-1]) {
      dp[i][j][k] = dp[i-1][j-1][k-1] + 1;
  } else {
      dp[i][j][k] = max({
          dp[i-1][j][k],
          dp[i][j-1][k],
          dp[i][j][k-1]
      });
  }
  ```

- **複雜度**：$O(n × m × l)$
- **分類**：P ✅（指數維度增加，但仍是可預測的多項式）

---

## 🔵 12. 最短公共超序列（SCS, Shortest Common Supersequence）

- 最小長度使得 A 與 B 都是它的子序列

  > A = "abac"
  >
  > B = "cab"
  >
  > → 最短公共超序列 S = "cabac"（長度 = 5）

- 可由 LCS 長度推出：`SCS = A 長度 + B 長度 - LCS 長度`

  ```cpp
  int scsLength = A.size() + B.size() - LCS(A, B);
  ```

  ```cpp
  int lcsLength(string A, string B) {
      int n = A.size(), m = B.size();
      vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
      for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= m; ++j)
              if (A[i - 1] == B[j - 1])
                  dp[i][j] = dp[i - 1][j - 1] + 1;
              else
                  dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      return dp[n][m];
  }
  int shortestCommonSupersequenceLength(string A, string B) {
      int lcs = lcsLength(A, B);
      return A.size() + B.size() - lcs;
  }
  ```

  

- **分類**：P ✅（直接使用 LCS 即可）

---

## 🔶 13. 編輯距離（Edit Distance）

- **定義**：將字串 A 轉換為字串 B 所需的最少編輯步驟（插入、刪除、替換）

  > A = "horse"
  > B = "ros"
  > → 最少操作為 3：h->(刪除), r保留, o保留, s保留, e->(刪除)

- **DP 陣列**：$dp[i][j] =$ 將 $A[0..i-1]$ 轉換成 $B[0..j-1]$ 的最少操作數

- **狀態轉移方程式**：
  
  ```cpp
      for (int i = 0; i <= n; ++i) dp[i][0] = i;
      for (int j = 0; j <= m; ++j) dp[0][j] = j;
  
      for (int i = 1; i <= n; ++i)
          for (int j = 1; j <= m; ++j) {
              if (A[i - 1] == B[j - 1])
                  dp[i][j] = dp[i - 1][j - 1];
              else
                  dp[i][j] = 1 + min({
                      dp[i - 1][j],    // delete
                      dp[i][j - 1],    // insert
                      dp[i - 1][j - 1] // replace
                  });
          }
  ```
  
- **複雜度**：$O(n × m)$

- **分類**：P ✅（完整 DP 遞推）

---

## 🔶 14. 最長回文子序列（Longest Palindromic Subsequence, LPS）

- **定義**：給定字串 S，找出最長的回文子序列長度
- **DP 陣列**：$dp[i][j] = S[i..j]$ 的最長回文子序列長度
- **狀態轉移方程式**：
  ```cpp
      for (int i = 0; i < n; ++i)
          dp[i][i] = 1;
  
      for (int len = 2; len <= n; ++len) {
          for (int i = 0; i <= n - len; ++i) {
              int j = i + len - 1;
              if (S[i] == S[j])
                  dp[i][j] = (len == 2) ? 2 : dp[i + 1][j - 1] + 2;
              else
                  dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
          }
      }
  ```
- **初始化**：$dp[i][i] = 1$
- **複雜度**：$O(n²)$
- **分類**：P ✅（標準區間 DP）

---

## 🔶 15. 最長公共子字串（Longest Common Substring）

- **定義**：兩字串中連續相等的最長子串長度
- **DP 陣列**：$dp[i][j] =$ 以 $A[i-1], B[j-1]$ 結尾的最長公共子字串長度
- **狀態轉移方程式**：
  ```cpp
  for (int i = 1; i <= n; ++i)
     for (int j = 1; j <= m; ++j)
         if (A[i - 1] == B[j - 1]) {
             dp[i][j] = dp[i - 1][j - 1] + 1;
             maxLen = max(maxLen, dp[i][j]);
          }
  ```
- **答案**：取所有 $dp[i][j]$ 最大值
- **複雜度**：$O(n × m)$
- **分類**：P ✅（簡單 DP）

---

## 🔶 16. 最長回文子字串（Longest Palindromic Substring）

- **定義**：在一個字串中找出最長的「連續」回文子字串（不是子序列）
- **DP 陣列**：$dp[i][j] = S[i..j]$ 是否為回文字串$（bool）$
- **狀態轉移方程式**：
  
  ```cpp
      for (int i = 0; i < n; ++i)
          dp[i][i] = true;
  
      for (int len = 2; len <= n; ++len) {
          for (int i = 0; i <= n - len; ++i) {
              int j = i + len - 1;
              if (s[i] == s[j]) {
                  if (len == 2)
                      dp[i][j] = true;
                  else
                      dp[i][j] = dp[i + 1][j - 1];
              }
              if (dp[i][j] && len > maxLen) {
                  maxLen = len;
                  start = i;
              }
          }
      }
  ```
- **初始化**：`dp[i][i] = true`（單字元一定是回文）
- **答案**：記錄 `j - i + 1` 最長的位置對應回文子字串
- **複雜度**：O(n²)
- **分類**：P ✅（完全可用 DP 表建構，實作簡單）

---

## ✅ 總表對照：

| 題型編號 | 題型名稱                      | 狀態 / 方法                 | 複雜度     | 分類說明              |
| -------- | ----------------------------- | --------------------------- | ---------- | --------------------- |
| 1        | 經典 LIS                      | `dp[i]` 遞推                | O(n²)      | P ✅ 多項式可解        |
| 2        | LIS（二分優化）               | tails + lower_bound         | O(n log n) | P ✅ 高效貪婪+查詢     |
| 3        | 非嚴格遞增 LNDS               | `nums[j] ≤ nums[i]`         | O(n²)      | P ✅ 相同結構          |
| 4        | 最長遞減子序列 LDS            | 原數列反轉處理              | O(n²)      | P ✅ 結構類似          |
| 5        | LIS 條數統計                  | `count[i]` 統計組合數       | O(n²)      | P ✅ 仍為 DP 累計      |
| 6        | 固定長度 K 的最小字典序 LIS   | 貪婪 + 回溯策略             | O(n²)~     | P ✅ 綜合演算法        |
| 7        | Online LIS                    | BIT / Segment Tree          | O(n log n) | P ✅ 查詢更新皆 log 級 |
| 8        | 回溯 LIS 實際路徑             | 使用 prev[] 陣列逆推        | O(n²)      | P ✅ 附加結構          |
| 9        | 最長共同子序列（LCS）         | `dp[i][j]` 雙字串遞推       | O(n×m)     | P ✅ 標準 DP           |
| 10       | 回溯 LCS 路徑                 | prev[][] 路徑重建           | O(n×m)     | P ✅ 同上延伸          |
| 11       | LCS on 3 strings              | `dp[i][j][k]` 三維遞推      | O(nml)     | P ✅ 三維多項式        |
| 12       | 最短公共超序列（SCS）         | 長度 = A+B−LCS              | O(n×m)     | P ✅ 推導形式          |
| 13       | 編輯距離（Edit Distance）     | 插入/刪除/替換 三選一       | O(n×m)     | P ✅ 動態規劃遞推      |
| 14       | 最長回文子序列（LPS）         | 區間 DP, 回文特性           | O(n²)      | P ✅ 區間狀態遞推      |
| 15       | 最長公共子字串                | 結尾遞推 + 歸零             | O(n×m)     | P ✅ 簡單表格遞推      |
| 16       | 最長回文子字串（子串≠子序列） | `dp[i][j]` 為 bool 判斷回文 | O(n²)      | P ✅ 窗口遞推式 DP     |

---

