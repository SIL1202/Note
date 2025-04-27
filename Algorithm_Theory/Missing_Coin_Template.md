# Missing Coin Sum Template

## 題目簡介

> 給一些數字，每個可以使用一次，問：最小無法累加出來的正數是什麼？

---

## 記憶關鍵：關鍵詞

> **從1開始找空缺，遇gap就停，最大能累加一路累加。**

---

## 模板流程：固定動作

1. 對全部數字排序 (由小到大)
2. 設 `coinSum = 1`
3. 循環每個 a[i] :
   - 如果 a[i] 小於等於 coinSum，把 a[i] 加入 coinSum
   - 如果 a[i] 大於 coinSum，表示沒路接，答案就是 coinSum

---

## 簡潔解釋

- **coinSum** ＝ 我最想要累加的盡頭正數
- 有能力累加就把 coinSum 往上翻，一直翻
- 一遇到無法累加，就是答案

---

## 視覺畫面：數字之橋

想像 coinSum 是一條準備要跨過的橋：
- 小硬幣跟 coinSum 一起擺上去
- 能連上就繼續，連不上就掉了
- 掉的那個數，就是最小無法累加的數

---

## 演算法範例 (C++)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define ll long long

int main() {
    int n;
    cin >> n;
    vector<ll> a(n);
    for (ll &x : a) cin >> x;

    sort(a.begin(), a.end());
    ll coinSum = 1;

    for (int i = 0; i < n; i++) {
        if (a[i] > coinSum) break;
        coinSum += a[i];
    }

    cout << coinSum << endl;
}
```

---

## 最後應急聲明

- **coinSum 不是現金，是能累加的盡頭值**！
- 每第一次無法連接的地方，就是答案！

---

# Missing Coin Sum：想起就是 「從1開始，累加蓋橋，遇空缺停。」

# 無限硬幣問題：最小不可湊出數（動態規劃解法）
### 核心思想
> 用 dp[i] 表示數字 i 是否能被硬幣湊出，逐步構建解。

```cpp
vector<bool> dp(1000, false); // 範圍需足夠大（覆蓋可能答案）
dp[0] = true;                // base case：0元可不選任何硬幣

for (int i = 0; i < dp.size(); ++i) {
    if (dp[i]) {              // 若i可被湊出，則i+coin也可被湊出
        for (int coin : coins) {
            if (i + coin < dp.size()) { // 避免越界
                dp[i + coin] = true;    // 標記為可湊出
            }
        }
    }
}
```
關鍵點備註
1. 初始化：

* dp[0] = true 是關鍵，代表「不選硬幣」的狀態。

* 陣列大小需足夠（例如設為 1000），確保能覆蓋答案。

2. 遞推邏輯：

* 外層循環：遍歷所有數字 i，檢查是否能從 i 遞推到 i+coin。

* 內層循環：對每個硬幣面額，標記 i+coin 為可湊出。

3. 找答案：

* 從 min_coin + 1 開始掃描 dp，第一個 dp[x] == false 的 x 即為答案。

* 範例：coins = [5,6,7] 時，dp[8] 是第一個 false。

4. 優化提示：

* 若硬幣已排序，可提前終止（當 i > target 時跳出）。

* 實際題目中，需先檢查 GCD(coins) == 1（否則無解）。

#### 時間複雜度
* 時間：O(N * M)，其中 N 是 dp 陣列大小，M 是硬幣數量。

* 空間：O(N)，用於存儲 dp 陣列。
