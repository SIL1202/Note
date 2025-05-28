#include <stdio.h>
#define MAX 100

// 定義比較函式的型別：接受兩個 void*，回傳 int（用來比較大小）
typedef int (*comFunc)(void *a, void *b);

// 定義泛型優先佇列結構
typedef struct PriorityQueue {
  void *items[MAX]; // 儲存資料的陣列（每個元素都是 void*，可泛型）
  int32_t size;     // 當前佇列大小（已插入元素數量）
  comFunc cmp;      // 比較函式，用來維持 heap 順序
} PriorityQueue;

// 交換兩個指標的內容（heap 排序時會用到）
void swap(void **a, void **b) {
  void *temp = *a;
  *a = *b;
  *b = temp;
}

// 從 index 開始往上調整（heapify-up），維持 min-heap 結構
void heapifyUp(PriorityQueue *pq, int32_t index) {
  if (index && pq->cmp(pq->items[(index - 1) / 2], pq->items[index]) > 0) {
    swap(&pq->items[(index - 1) / 2], &pq->items[index]);
    heapifyUp(pq, (index - 1) / 2);
  }
}

// 將一個值插入 heap 中
void enqueue(PriorityQueue *pq, void *value) {
  if (pq->size == MAX) {
    printf("Priority queue is full\n");
    return;
  }

  pq->items[pq->size++] = value; // 插入到尾端
  heapifyUp(pq, pq->size - 1);   // 往上調整
}

// 從 index 開始往下調整（heapify-down），維持 min-heap 結構
void heapifyDown(PriorityQueue *pq, int32_t index) {
  int smallest = index;
  int left = index * 2 + 1;
  int right = index * 2 + 2;

  // 找出左右子節點中較小者
  if (left < pq->size && pq->cmp(pq->items[smallest], pq->items[left]) > 0)
    smallest = left;

  if (right < pq->size && pq->cmp(pq->items[smallest], pq->items[right]) > 0)
    smallest = right;

  // 若子節點比當前節點小，交換並遞迴處理
  if (smallest != index) {
    swap(&pq->items[index], &pq->items[smallest]);
    heapifyDown(pq, smallest);
  }
}

// 從 heap 中移除並回傳最小值（根節點）
void *dequeue(PriorityQueue *pq) {
  if (!pq->size) {
    printf("Priority queue is empty\n");
    return NULL;
  }

  void *temp = pq->items[0];            // 取出最小值（根節點）
  pq->items[0] = pq->items[--pq->size]; // 將最後一個節點移到根
  heapifyDown(pq, 0);                   // 往下調整
  return temp;
}

// int 型別的比較函式（min-heap：小的在前）
int cmpInt(void *a, void *b) { return *(int *)a - *(int *)b; }

// 印出整個 heap 的內容（透過 dequeue 取出）
void print(PriorityQueue *pq) {
  int *out;
  while ((out = (int *)dequeue(pq)) != NULL) {
    printf("dequeued: %d\n", *out);
  }
}

// 主程式測試
int main() {
  PriorityQueue priority_queue = {{0}, 0, cmpInt}; // 初始化 heap

  int a = 1, b = 2, c = 3, d = 4;

  enqueue(&priority_queue, &a);
  enqueue(&priority_queue, &b);
  enqueue(&priority_queue, &c);
  enqueue(&priority_queue, &d);

  print(&priority_queue); // 印出排序結果
  return 0;
}
