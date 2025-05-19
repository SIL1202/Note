# C++ 專案筆記：`static` 的五種用法

在 C++ 中，`static` 關鍵字根據使用位置不同，有五種常見且意義不同的用途：

---

## ✅ 1. Local Static Variable（區域靜態變數）

* 使用位置：函式內部
* 僅初始化一次，函式結束後變數不消失，會保留先前的值。

```cpp
void counter() {
    static int a = 0;
    a++;
    std::cout << "a = " << a << std::endl;
}
```

---

## ✅ 2. Global Static Variable（全域靜態變數）

* 使用位置：檔案最外層
* 與一般全域變數不同的是，它**只能在該檔案內存取**（internal linkage）。

```cpp
static int a = 10; // Only accessible in this translation unit
```

---

## ✅ 3. Static Member Variable（類別靜態變數）

* 使用位置：類別中
* 屬於「類別本身」而不是物件，所有物件共用一份變數。

```cpp
class Tool {
public:
    static int c;
};
int Tool::c = 0;
```

---

## ✅ 4. Static Member Function（類別靜態函式）

* 使用位置：類別中
* 不屬於任何物件，可直接用 `Class::function()` 呼叫。
* **只能存取其他 static 成員**。

```cpp
class Tool {
public:
    static int count;
    static void foo() { count++; }
};
int Tool::count = 0;
```

---

## ✅ 5. File-Static Function（檔案靜態函式）

* 使用位置：類別外部，通常在 `.cpp` 檔內
* 限定此函式只能在該檔案中使用，無法被其他檔案 `extern` 存取。
* 目的：**封裝實作細節，避免命名衝突**

```cpp
static void helper() {
    std::cout << "Internal use only.\n";
}
```

---

## 📌 小結比較表

| 用法類型           | 位置   | 是否共用 | 是否限制外部存取  | 典型用途            |
| -------------- | ---- | ---- | --------- | --------------- |
| 區域 static 變數   | 函式內  | ❌    | ✅（僅該函式內）  | 狀態保留、計數器        |
| 全域 static 變數   | 檔案頂部 | ✅    | ✅（僅該檔案）   | 封裝常數或工具變數       |
| 類別 static 成員變數 | 類別中  | ✅    | ❌（可公開或私有） | 計數器、全體共用資源      |
| 類別 static 函式   | 類別中  | ✅    | ❌（可公開或私有） | 類別工具函式、不依譜物件的邏輯 |
| 全域 static 函式   | 檔案內  | ✅    | ✅（僅該檔案）   | 工具函式、避免外部誤用與衝突  |
