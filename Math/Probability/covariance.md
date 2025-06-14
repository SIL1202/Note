# Covariance（共變異數）

---
title: Covariance
tags: [probability, statistics, correlation, PCA]
created: 2025-05-29


## 定義

給定兩個隨機變數 $X$ 和 $Y$，其共變異數為：

$Cov(X, Y) = E[(X - \mu_X)(Y - \mu_Y)$

也可以寫成：

$Cov(X, Y) = E[XY] - E[X]E[Y]$

---

## 直觀意義

- 衡量兩個變數的**聯合變動方向**
- $Cov(X, Y) > 0$：同向變動
- $Cov(X, Y) < 0$：反向變動
- $Cov(X, Y) = 0$：線性無關（但不代表完全無關）

---

## 單位說明

- 單位為：
  $$
  \text{單位}_X \times \text{單位}_Y
  $$
  
- 若 X 是「公分」、Y 是「公斤」，則 Cov(X, Y) 的單位是「公分 × 公斤」
- 因此不可直接比較不同變數的 Cov 值大小

---

## 計算方式

### 離散型資料：

$$
\text{Cov}(X, Y) = \sum_x \sum_y (x - \mu_X)(y - \mu_Y)p(x, y)
$$



### 連續型資料：

$$
\text{Cov}(X, Y) = \int \int (x - \mu_X)(y - \mu_Y) f(x, y) dxdy
$$



---

## 實作範例（C++）

```cpp
// Covariance 實作略（可連結到 code 範例）
