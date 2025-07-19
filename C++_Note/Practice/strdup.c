#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Entry 結構：用來儲存 key-value pair
typedef struct {
  char *key;
  char *value;
} Entry;

// 插入 key-value 時，使用 strdup 複製 key 與 value 的內容
// 這樣 entry 的欄位就不會受外部變數的修改影響
void insert(Entry *e, char *key, char *value) {
  e->key = strdup(key);     // 開一塊新記憶體，複製 key 字串內容
  e->value = strdup(value); // 同上，複製 value
}

int main() {
  Entry e;

  // 原始的 key 與 value 是在 stack 上的陣列
  char key[100] = "apple";
  char val[] = "red";

  // 將 key/value 插入 Entry 結構中
  insert(&e, key, val);

  // ❗️這裡修改了原本 key 的內容
  // 如果 insert() 裡面沒用 strdup，只是指過去的話，這裡改會直接影響 e.key
  strcpy(key, "banana");

  // 印出 Entry 的內容
  // 因為使用 strdup，e.key 與 e.value 指向自己的 heap 空間，不會被外部改到
  printf("[%s, %s]\n", e.key, e.value); // 預期輸出：[apple, red]

  // 記得釋放 strdup 配的記憶體，避免 memory leak
  free(e.key);
  free(e.value);

  return 0;
}
