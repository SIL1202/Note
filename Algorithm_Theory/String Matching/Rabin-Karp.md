# 字串匹配：Rabin-Karp

---

### 🧪 題目說明

### 	給定一個文字 text 與一個模式 pattern，找出所有出現在 text 中的 pattern 的起始位置。

---

## 📦 核心概念：滾動哈希（Rolling Hash）

- 使用哈希值來比較子字串是否相等。

- 若哈希值不同：一定不相等

- 若哈希值相同：需進一步字串比對（避免碰撞誤判）

---


## 🧠 哈希公式（以 base = 31 為例）

- 將字元視為 1~26 的數字（a=1, b=2, ..., z=26）

​	$H(s) = s[0]*base^(m-1) + s[1]*base^(m-2) + ... + s[m-1]*base^0  (mod MOD)$

---

## ❓為什麼要  - 'a' + 1

- 'a' 的 ASCII 是 97，所以 c - 'a' 可得 'a' → 0，'b' → 1，以此類推。
- 為了方便從 1 開始編號（非 0）：加上 +1 使得 'a' → 1，'z' → 26
- 這樣數字範圍較小，且易於計算哈希值，避免溢位。

---

```cpp
#define ll long long
const int BASE = 31;
const int MOD = 1e9+7; // 質數

ll computeHash(const string &s){
	ll hash = 0;
	for(char c: s)
		hash = (hash * BASE + (c - 'a' + 1)) % MOD;
	return hash;
}

void RabinKarp(string text, string pattern){
  int n = text.length();
  int m = pattern.length();
  
  if(m > n) return;
  
  ll patternHash = computeHash(pattern);
  ll windowHash = computeHash(text.substr(0, m));
  
  // calculate the power
  vector<int> power(m);
  power[0] = 1;
  for(int i=1; i<m ;++i){
    power[i] = (power[i-1] * BASE) % MOD;
  }
  
  for(int i = 0; i < n - m + 1; ++i){
    if(windowHash == patternHash && 
       text.substr(i, m) == pattern)
			cout << "Pattern found at index: " << i << '\n';
    if(i < n - m){
      windowHash = (windowHash - (ll)(text[i] - 'a' + 1) * power[m - i - 1]) % MOD + MOD) % MOD;
      windowHash = (windowHash * BASE + (text[i] - 'a' + 1)) % MOd;
    }
  }
}
```

