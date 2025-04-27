# Kadane's Algorithm 筆記

## 題目描述
找出一個陣列中，**連續子陣列的最大總和 (Maximum subarray problem)**。  
子陣列必須是**連續**的，不能跳格。

---

## 思考流程
- 走到第 `i` 個數時，決定：
  - **要繼續累積**之前的總和 (`sum + a[i]`)？
  - **還是重新開始**，直接拿現在這個數 (`a[i]`)？
- 每次都取兩者中比較大的，更新 `sum`。
- 同時，每一步都更新目前遇過的最大總和 `best`。

---

## 演算法核心
```cpp
sum = max(a[i], sum + a[i]);
best = max(best, sum);
```
- `sum`：目前到第 `i` 個的**最好連續總和**。
- `best`：歷史上遇過的最大子陣列總和。

---

## 程式碼範例
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    long long best = a[0], sum = a[0];
    for (int i = 1; i < n; i++) {
        sum = max(a[i], sum + a[i]);
        best = max(best, sum);
    }

    cout << best << endl;
}
```

---

## 時間與空間複雜度

| 複雜度 | 說明 |
|:---|:---|
| 時間複雜度 O(n) | 每個元素只看一次 |
| 空間複雜度 O(n) | 儲存輸入陣列 |

---

## 小例子（步驟細解）

輸入：

```
n = 8
a = [-1, 3, -2, 5, 3, -5, 2, 2]
```

計算過程：

| i | a[i] | sum = max(a[i], sum + a[i]) | best = max(best, sum) |
|:-:|:-:|:-:|:-:|
| 0 | -1 | -1 | -1 |
| 1 | 3 | 3 | 3 |
| 2 | -2 | 1 | 3 |
| 3 | 5 | 6 | 6 |
| 4 | 3 | 9 | 9 |
| 5 | -5 | 4 | 9 |
| 6 | 2 | 6 | 9 |
| 7 | 2 | 8 | 9 |

最終輸出 `9`。

---

## 核心一句語總算

> 如果累積起來變爛，就放棄重開；如果還可以繼續變大，就接著加下去。
