#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 10

// Node definition
typedef struct Entry {
  char *key;
  char *value;
  struct Entry *next;
} Entry;

// Hash Table structure
typedef struct HashTable {
  Entry *bucket[TABLE_SIZE];
} HashTable;

// djb2 字串 hash function，會回傳一個 unsigned long 值
unsigned int hash(const char *key) {
  unsigned long hash = 5381;
  int c;
  while ((c = *key++)) {
    hash = ((hash << 5) + hash) + c; // hash = hash * 33 + c
  }
  return hash;
}

// 建立新的 HashTable
HashTable *create_table() {
  HashTable *table = (HashTable *)malloc(sizeof(HashTable));
  for (int i = 0; i < TABLE_SIZE; i++)
    table->bucket[i] = NULL;
  return table;
}

// 插入 key-value pair，如果 key 已存在則更新 value
void insert(HashTable *table, char *key, char *value) {
  unsigned int index = hash(key) % TABLE_SIZE;
  Entry *entry = table->bucket[index];

  // 檢查是否已存在該 key
  while (entry) {
    if (strcmp(entry->key, key) == 0) {
      free(entry->value);
      entry->value = strdup(value);
      return; // 找到後更新完直接 return，避免重複插入
    }
    entry = entry->next;
  }

  // 如果 key 不存在，創建新節點並插入 bucket 開頭
  entry = (Entry *)malloc(sizeof(Entry));
  entry->key = strdup(key);
  entry->value = strdup(value);
  entry->next = table->bucket[index];
  table->bucket[index] = entry;
}

// 查詢 key 對應的 value，找不到時回傳 NULL
char *get(HashTable *table, char *key) {
  unsigned int index = hash(key) % TABLE_SIZE;
  Entry *entry = table->bucket[index];
  while (entry) {
    if (strcmp(entry->key, key) == 0)
      return entry->value;
    entry = entry->next;
  }
  return NULL;
}

// 刪除指定 key 的節點，若存在則釋放其記憶體
void delete(HashTable *table, const char *key) {
  unsigned int index = hash(key) % TABLE_SIZE;
  Entry *entry = table->bucket[index];
  Entry *prev = NULL;
  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      if (prev == NULL) {
        table->bucket[index] = entry->next;
      } else {
        prev->next = entry->next;
      }
      free(entry->key);
      free(entry->value);
      free(entry);
      return;
    }
    prev = entry;
    entry = entry->next;
  }
}

// 釋放整個 HashTable 的所有記憶體
void free_table(HashTable *table) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    Entry *entry = table->bucket[i];
    while (entry) {
      Entry *next = entry->next;
      free(entry->key);
      free(entry->value);
      free(entry);
      entry = next;
    }
  }
  free(table);
}

// 主程式示範 HashTable 操作
int main() {
  HashTable *ht = create_table();

  insert(ht, "apple", "red");
  insert(ht, "banana", "yellow");
  insert(ht, "grape", "purple");

  printf("apple => %s\n", get(ht, "apple"));
  printf("banana => %s\n", get(ht, "banana"));

  delete (ht, "banana");
  printf("banana => %s\n", get(ht, "banana")); // 應為 NULL

  free_table(ht);
  return 0;
}
// clang-format off
//
// Stack（主程式區域變數）
// ─────────────────────────────
// ht ────────┐
//            ▼
// Heap（動態配置空間）
// ─────────────────────────────
// [HashTable 結構體]
// table ─────┐
//            │
//            ▼
// ┌───────────────────────────────┐
// │ buckets[0] ─────► NULL        │
// │ buckets[1] ─────► NULL        │
// │ buckets[2] ─────► NULL        │
// │    ...                        │
// │ buckets[TABLE_SIZE-1]  ─► NULL│
// └───────────────────────────────┘
//
// After insert one data
// ht ────────┐
//            ▼
// ┌─────────────────────────────────────────────────────┐
// │ ...                                                 │
// │ buckets[7] ─────► [Entry: key="apple", val="red", next=NULL] ┐
// │ ...                                                 │        │
// └─────────────────────────────────────────────────────┘        ▼
//                                                          Heap 中新的Entry結構
// clang-format on
