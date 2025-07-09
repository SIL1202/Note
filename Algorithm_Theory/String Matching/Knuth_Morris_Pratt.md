# 字串匹配：暴力法 vs KMP 演算法 （簡潔版）

---

### 🧪 題目說明
給定一個文字 `text` 與一個模式 `pattern`，找出所有出現在 `text` 中的 `pattern` 開始位置。

---

## 🔨 暴力法：時間複雜度 O(n * m)

```cpp
void BruteForceMatch(string text, string pattern) {
  int n = text.length();
  int m = pattern.length();

  for (int i = 0; i <= n - m; ++i) {
    int j = 0;
    while (j < m && text[i + j] == pattern[j]) {
      ++j;
    }
    if (j == m) {
      cout << "Pattern found at index: " << i << '\n';
    }
  }
}
```

- 每次從 text 中某個位置開始暴力比對 pattern
- 若發現不符就換下一個位置，效率低

---

## ⚡ KMP 演算法：時間複雜度 O(n + m)

#### 🔧 Step 1：建立 LPS 表（Longest Prefix Suffix）

```cpp
vector<int> LPS(string pattern) {
  int n = pattern.length();
  vector<int> lps(n);
  int len = 0; // 當前已匹配的長度
  int i = 1;

  while (i < n) {
    if (pattern[i] == pattern[len]) {
      len++;
      lps[i] = len;
      i++;
    } else if (len != 0) {
      len = lps[len - 1];
    } else {
      lps[i] = 0;
      i++;
    }
  }
  return lps;
}
```

- `lps[i]` 表示 pattern[0..i] 的最長前綴也是後綴的長度
- 用來在主比對失敗時快速跳位（避免重複比對）

#### 🔍 Step 2：進行主比對

```cpp
void KMP(string text, string pattern) {
  int n = text.length();
  int m = pattern.length();
  vector<int> lps = LPS(pattern);

  int i = 0, j = 0;
  while (i < n) {
    if (text[i] == pattern[j]) {
      i++; j++;
    
       if (j == m) {
         cout << "Pattern found at index: " << i - j << '\n';
         j = lps[j - 1];
       }
    } else if (i < n && text[i] != pattern[j]) {
      if (j != 0) j = lps[j - 1];
      else i++;
    }
  }
}
```

- `i` 指向 text，`j` 指向 pattern
- 若比對成功，則前進；
- 若比對失敗，依據 `lps` 進行跳位，避免從頭開始比對

---

## **✨ 精簡版 KMP：一行內處理條件與計數**

```cpp
void KMP_Concise(string s, string p) {
  int n = s.length();
  int m = p.length();

  // 建立 lps 表
  vector<int> lps(m);
  for (int i = 1, j = 0; i < m;) {
    if (p[i] == p[j])
      lps[i++] = ++j;
    else
      j ? j = lps[j - 1] : lps[i++] = 0;
  }

  // 進行比對
  int count = 0;
  for (int i = 0, j = 0; i < n;) {
    if (s[i] == p[j]){
      ++i, ++j;
      if (j == m)
        ++count, j = lps[j - 1];  // 匹配成功，更新 j 繼續找
    } else if (i < n && s[i] != p[j])
      j ? j = lps[j - 1] : ++i; // 失敗但 j ≠ 0 就跳位，否則 i++
  }
  cout << "Count from concise version: " << count << '\n';
}
```

📌 **說明**：

- 簡化整體流程，將跳位與成功條件整合在迴圈內。
- 若只關心出現次數，可使用 count 變數統計。

---

## 🧪 測試程式：

```cpp
int main() {
  string pattern = "ababcabab";
  string text = "bababababcababcabab";

  cout << "[Brute Force]\n";
  BruteForceMatch(text, pattern);

  cout << "\n[KMP Algorithm]\n";
  KMP(text, pattern);

  return 0;
}
```
