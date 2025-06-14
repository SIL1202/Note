# Correlation（相關係數）

---
title: correlation
tags: [probability, correlation]

## 📘 定義

相關係數（皮爾森）定義為：

$$
\rho_{X, Y} = \frac{\text{Cov}(X, Y)}{\sigma_X \cdot \sigma_Y}
$$

## 意義與範圍

- 衡量 X 與 Y 之間的**線性相關程度**
- 範圍：
    $$
     -1 \le \rho \le 1
    $$
    
    - $\rho = 1$ : 完全正相關
    - $\rho = -1$ : 完全負相關
    - $\rho = 0$：無線性關聯



## 無單位

- 因為被標準差相除，**無單位**
- 可以比較不同變數組合之間的相關性強弱


## 實作範例（C++）

```cpp
// correlation 實作略（可連結到 code 範例）
