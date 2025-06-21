# Shortest Path Algorithms

This repository contains implementations of three classic shortest path algorithms in C++:

* **Dijkstra's Algorithm**
* **Bellman-Ford Algorithm**
* **Floyd-Warshall Algorithm**

Each algorithm is suited for different graph characteristics. Below is a description of each one, including use cases, advantages, and key implementation details.

---

## 1. Dijkstra's Algorithm

**File:** `Dijkstra.cpp`

### Overview

Dijkstra's algorithm finds the shortest path from a single source node to all other nodes in a graph with non-negative edge weights.

### Features

* Time complexity: $O((V + E) \log V)$ using a priority queue (min-heap).
* Efficient for sparse graphs.
* Cannot handle negative weights.

### **Note**

可以用 **priority_queue** 或是 **set** 這兩個 **Min-Heap** 的容器

因為排 pair 排的 pq.first 所以存的方式是 { dist, node }

比較要注意的地方是 priority_queue 跟 set 都要處理舊的資料，因為同一個節點會被重複走到，但是容器裡面存在的舊節點可能會在處理同一個節點時被拿出來所以要刪掉或跳過。

**priority_queue**：

```c++
 if (d > dist[u])
   continue;
```

**set**：

```c++
 if (dist[v] != INF)
   s.erase({dist[v], v});
```

舉例：

```c++
1 → 2 (cost 3)
1 → 3 (cost 2)
2 → 4 (cost 2)
3 → 4 (cost 5)
```

處理順序：

1. 初始：{0, 1}

2. 處理 1 → 推入 {3, 2} 和 {2, 3}

3. 處理 3 → 推入 {7, 4}

4. 處理 2 → 推入 {5, 4}（這時候 4 已經進來過了）

   你就會有兩筆**關於節點 4**的資料在資料結構中：

   {7, 4}, {5, 4}

   > 同一個節點（4），會有 **兩筆不同距離** 的紀錄存在！
   >
   > 所以要比較 d, dist[u] 如果舊的比較大那就跳過。



### Use Case

* GPS navigation
* Network routing

### Input Format

* Number of nodes and edges.
* List of edges with weights.
* Source vertex.

### Output

* Shortest distance from source to each node.

---

## 2. Bellman-Ford Algorithm

**File:** `BellmanFord.cpp`

### Overview

Bellman-Ford finds the shortest paths from a single source node to all others and can detect negative weight cycles.

### Features

* Time complexity: $O(V \cdot E)$
* Works with negative edge weights.
* Detects negative cycles.

### Note 

**Bellman** 跟 **Dijkstra** 很像，只差在這裡要分別處理每一個點的出邊（叫做 relaxation），並重複 $V-1$ 次，因為最後一次要檢查是不是負環，如果是的話就結束不是的話就輸出 dist。

### Use Case

* Currency arbitrage detection
* Graphs with negative edge weights

### Input Format

* Number of vertices and edges.
* List of edges: (from, to, weight).
* Source vertex.

### Output

* Shortest distances from source, or message if a negative cycle is detected.

---

## 3. Floyd-Warshall Algorithm

**File:** `FloydWarshall.cpp`

### Overview

Floyd-Warshall is an all-pairs shortest path algorithm using dynamic programming.

### Note

用動態規劃來紀錄所有 Source/Start node 到其他點的距離這樣會比跑 n 次的 **Dijkstra** 還來的快和省空間，狀態轉移方程為 `dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])`

### Features

* Time complexity: $O(V^3)$
* Simple to implement.
* Handles negative weights (but no negative cycles).

### Use Case

* Finding shortest path between all pairs of nodes.
* Network analysis.

### Input Format

* Number of nodes.
* Adjacency list or matrix with edge weights.

### Output

* A matrix where `dist[i][j]` is the shortest distance from node `i` to `j`.
