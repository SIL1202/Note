# Merge Sort 筆記與遞迴考題整理

## 筆記

### 1. Merge Sort 的遞迴過程
- `merge_sorted_recursion(a, l, r)`：透過 **Divide and Conquer（分治法）** 來排序陣列。
- 每次遞迴都將陣列分成左右兩半，直到只剩一個元素。
- 分割後，遞迴合併兩個已排序的子陣列。

### 2. `merge_sorted_array(a, l, mid, r)` 合併過程
- 先複製左右兩個子陣列：
  ```cpp
  int left_length = mid - l + 1;
  int right_length = r - mid;
  int left_array[left_length];  // 左側子陣列
  int right_array[right_length]; // 右側子陣列
  ```
- 逐步比較 `left_array` 和 `right_array`，並填回 `a[]`。
- 若其中一個子陣列已經填完，直接將另一個子陣列的剩餘部分複製回去。
- **條件判斷解釋：**
  
  ```
  //                   i
  //  left_array = 4 9 12
  //                 j
  // right_array = 5 8 14
  //                   k
  //           a = 4 5
  ```

  ```cpp
  if (i < left_length && (j >= right_length || left_array[i] <= right_array[j]))
  ```
  **這個條件的作用是決定應該選擇 `left_array[i]` 還是 `right_array[j]` 來填入結果陣列。條件分為三部分：**
  1. `i < left_length`：確保 `i` 還沒有超出 `left_array` 的範圍。
  2. `j >= right_length`：如果 `j` 超出了 `right_array` 的範圍，代表 `right_array` 已經用完，此時只能選擇 `left_array[i]`。
  3. `left_array[i] <= right_array[j]`：當 `left_array[i]` 的值較小時，應該選擇 `left_array[i]` 來確保排序結果正確。
  **這樣的判斷條件能夠確保合併時的穩定性，且能夠在 `right_array` 已經耗盡的情況下，仍然正確處理剩餘的 `left_array` 元素。**

### 3. Stack 與 Heap 的記憶體分配
- **Stack（堆疊）：**
  - 遞迴函數呼叫時，每次都會在 Stack 上建立新的 frame，包含 `l, r, mid` 及函數變數。
  - 遞迴深度為 `O(log N)`，若 `N` 很大（如 `10^6`），可能導致 **Stack Overflow**。
  - **筆記：** 若 `N` 過大，遞迴過深會導致 `Stack Overflow`，需使用 **迭代** 或 **Heap 分配** 暫存陣列。
- **Heap（堆）：**
  - `left_array` 和 `right_array` 預設在 **Stack 上** 分配，可能導致記憶體爆掉。
  - **筆記：** 建議使用 `new` 分配記憶體，避免 stack 限制。
  - 解決方法：改用 Heap 分配
    ```cpp
    int* left_array = new int[left_length];
    int* right_array = new int[right_length];
    ```
  - 使用完畢後記得釋放記憶體：
    ```cpp
    delete[] left_array;
    delete[] right_array;
    ```

### 4. Merge Sort 時間複雜度
- **Best / Average / Worst Case:** `O(N log N)`
- **遞迴呼叫次數：** `O(log N)` 層，每層 `O(N)` 合併。
- **筆記：** 遞迴的合併步驟是 `O(N)`，但總共有 `O(log N)` 層，所以整體複雜度是 `O(N log N)`。

⚠️ ## 遞迴考題

### **1. 遞迴深度與呼叫次數**
**問題：** 
假設對長度為 `N` 的陣列執行 `merge_sort`，`merge_sorted_recursion(a, l, r)` 最多會呼叫多少次？

**解答：**
- 遞迴深度為 `O(log N)`，每層合併的數量 `O(N)`。
- 總呼叫次數 `O(N log N)`。

---

### **2. 遞迴基底條件**
**問題：**
`merge_sorted_recursion(a, l, r)` 的基底條件是 `if (l < r)`，如果改成 `if (l <= r)` 會發生什麼情況？

**解答：**
- `l == r` 仍然會遞迴，造成 **無限遞迴**。
- **筆記：** 遞迴的基底條件應確保遞迴能終止，否則會導致 Stack Overflow。
- 正確條件應該是 `if (l < r)`，確保只有當區間長度 **至少為2** 才會繼續分割。

---

這些題型可以幫助你測試對 `merge_sort` 的理解，包括 **遞迴、記憶體管理、錯誤處理、最佳化技巧**，讓你在考試或面試時更有把握！


