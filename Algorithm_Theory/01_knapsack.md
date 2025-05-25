## 0/1 Knapsack: Three Solution Approaches

This document summarizes and compares three classic methods to solve the 0/1 Knapsack problem: **Backtracking**, **Branch and Bound**, and **Dynamic Programming**.

---

### 1. Backtracking (BT)

#### 🔍 Description:

Recursively explores all combinations of selecting or not selecting each item. At each level, we either include or exclude the current item.

#### ✅ Core Logic:

* Try all possible inclusion/exclusion paths.
* Track `currentWeight` and `currentValue`.
* Update `maxValue` at each leaf node.

#### ✂️ Pruning:

* Basic: Stop if `currentWeight > W`.
* Strong: Estimate maximum possible value from remaining items. If `currentValue + estimate <= maxValue`, prune.

#### ⏱️ Time Complexity:

* Worst case: **O(2^n)**

#### 📌 Notes:

* Easy to implement.
* Good for learning recursion and decision trees.
* Not efficient for large `n`.

### **Source Code**

```cpp
int maxValue = 0;

int RemainingValue(int i, int n, int W, int currentW, vector<int> &weights,
                   vector<int> &values) {
  int total = 0;
  for (int j = i; j < n; j++) {
    if (currentW + weights[j] <= W) {
      currentW += weights[j];
      total += values[j];
    } else
      break;
  }
  return total;
}

void Backtrack(int i, int n, int W, int currentW, int currentV,
               vector<int> &weights, vector<int> &values) {
  if (currentW > W)
    return;
  if (i == n) {
    maxValue = max(maxValue, currentV);
    return;
  }

  int remaining = RemainingValue(i, n, W, currentW, weights, values);
  if (currentV + remaining <= maxValue)
    return;

  Backtrack(i + 1, n, W, currentW + weights[i], currentV + values[i], weights,
            values);
  Backtrack(i + 1, n, W, currentW, currentV, weights, values);
}
```



---

### 2. Branch and Bound (B\&B)

#### 🔍 Description:

An optimization over Backtracking. It uses a queue (often a priority queue) to explore the most promising nodes first.

#### ✅ Core Logic:

* Each node keeps:

  * `level` (index of item considered)
  * `currentWeight`, `currentValue`
  * `bound`: upper bound estimate (using fractional knapsack)
* If `bound < maxProfit`, prune the branch.

#### 📦 Upper Bound:

* Greedily estimate the max possible value by allowing fractional items (only for estimation).

#### ⏱️ Time Complexity:

* Worst case: **O(2^n)**
* Practical performance: much faster due to strong pruning

#### 📌 Notes:

* Efficient for medium-size `n` (up to \~30)
* Requires sorting by value-to-weight ratio
* Uses a `priority_queue` to explore good nodes early

### Source Code

```cpp
struct Item {
  int weight, value;
  double ratio;
};

struct Node {
  int level, value, weight;
  double bound;
  bool operator<(const Node &other) const {
    return bound < other.bound; // max-heap
  }
};

double bound(Node u, int n, int W, const vector<Item> &items) {
  if (u.weight >= W)
    return 0;

  double profit_bound = u.value;
  int j = u.level;
  int totweight = u.weight;

  while (j < n && totweight + items[j].weight <= W) {
    totweight += items[j].weight;
    profit_bound += items[j].value;
    j++;
  }

  if (j < n)
    profit_bound += (W - totweight) * items[j].ratio;

  return profit_bound;
}

int knapsackBranchAndBound(int W, vector<Item> &items) {
  sort(items.begin(), items.end(),
       [](Item a, Item b) { return a.ratio > b.ratio; });

  priority_queue<Node> pq;
  Node u, v;
  u.level = 0, u.value = 0, u.weight = 0;
  u.bound = bound(u, items.size(), W, items);
  pq.push(u);

  int maxProfit = 0;
  while (!pq.empty()) {
    u = pq.top();
    pq.pop();

    if (u.bound <= maxProfit)
      continue;

    v.level = u.level + 1;

    // Try including item
    v.weight = u.weight + items[u.level].weight;
    v.value = u.value + items[u.level].value;
    if (v.weight <= W && v.value > maxProfit)
      maxProfit = v.value;
    v.bound = bound(v, items.size(), W, items);
    if (v.bound > maxProfit)
      pq.push(v);

    // Try excluding item
    v.weight = u.weight;
    v.value = u.value;
    v.bound = bound(v, items.size(), W, items);
    if (v.bound > maxProfit)
      pq.push(v);
  }

  return maxProfit;
}
```



---

### 3. Dynamic Programming (DP)

#### 🔍 Description:

Builds a table where each cell `dp[i][w]` represents the maximum value using the first `i` items within weight `w`.

#### ✅ Core Logic:

* Transition:

  > 2D
  
  ```cpp
  dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weight[i]] + value[i]);
  ```
  
  > 1D
  
  ```cpp
  dp[w] = max(dp[w], dp[w-weight[i]] + value[i]);
  ```
  
  
  
* Can be optimized to 1D array (rolling DP)

#### ⏱️ Time & Space Complexity:

* Time: **O(n \* W)**
* Space: **O(n \* W)** (or **O(W)** with 1D optimization)

#### 📌 Notes:

* Most efficient for large `W`
* Guarantees exact optimal solution
* Pseudo-polynomial time due to dependence on value of `W`

### Source Code

```cpp
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
```



---

### 🔚 Summary Table:

| Method              | Time Complexity             | Space            | Notes                                   |
| ------------------- | --------------------------- | ---------------- | --------------------------------------- |
| Backtracking        | O(2^n)                      | O(n)             | Simple, but exponential                 |
| Branch and Bound    | O(2^n) (better in practice) | O(n) + PQ        | Fast for small/medium `n`               |
| Dynamic Programming | O(n \* W)                   | O(n \* W) / O(W) | Best for large `W`, exact and efficient |
