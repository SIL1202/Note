# C++ 運算子重載與傳遞 (Operator Overloading & Chaining)

## 1. 概念
在 C++ 中，當 `std::cout << obj;` 被執行時，如果 `obj` 是一個類別（如 `Node<T>`），則 `operator<<` 可能會 **先處理 `Node<T>`，然後再傳遞到 `T` 的 `operator<<`**。

這種 **運算子傳遞（Operator Chaining）** 技巧，讓 `std::cout << object;` 能夠適用於不同的類別設計。

---

## 2. 程式碼示例

### **📌 `operator<<` 透過 `Node<T>` 傳遞到 `T`**

```cpp
#include <iostream>
template <class T> class Node {
public:
  Node() { data = new T; }
  Node(T d) { data = new T(d); }
  ~Node() { delete data; }

  Node &operator=(const T &d) {
    *data = d;
    return *this;
  }

  friend std::ostream &operator<<(std::ostream &out, const Node<T> &d) {
    out << (*d.data);
    return out;
  }

  friend std::istream &operator>>(std::istream &in, Node<T> &d) {
    in >> (*d.data);
    return in;
  }

  void setData(T d) { (*data) = d; }

  T &getData() const { return *data; }

protected:
  T *data; // ***這裡用指標是為了可以存取 A 類型***
};

class A {
public:
  const int x;
  A(int v) : x(v) {}

  friend std::ostream &operator<<(std::ostream &out, const A &other) {
    out << other.x;
    return out;
  }
};

int main() {
  Node<A> n1(A(10));
  Node<A> n2(A(20));

  std::cout << n1;
}
```

---

## 3. **運作流程**

當執行 `std::cout << n1;` 時，會依序執行以下步驟：

1. `std::cout << n1;`  
   - **呼叫 `Node<A>` 的 `operator<<`**

2. `out << (*n1.data);`  
   - **`*n1.data` 會變成 `A(10)`**

3. `std::cout << A(10);`  
   - **呼叫 `A` 的 `operator<<`**

4. `std::cout << 10;`  
   - **輸出 `10`**

**➡️ 最終輸出結果：**
```
10
```

---

## 4. **為什麼 `data` 需要是指標？**

### **原因：為了讓 `Node<T>` 可以處理 `A` 類型**
- **如果 `data` 直接存 `T`，當 `T` 內有 `const` 成員時，`operator=` 會導致錯誤。**
- **使用指標 (`T*`)，可以讓 `Node<T>` 只負責存取 `T`，而不改變 `T` 的結構或限制。**

### **可能的錯誤 & 解決方案**

❌ **錯誤**
```cpp
class A {
public:
  const int x;
  A(int v) : x(v) {}
};

Node<A> n1(A(10));
Node<A> n2(A(20));
n1 = n2;  // ❌ 無法編譯，因為 A 內有 const 變數
```

✅ **解決方法 1：刪除 `operator=`，改用 `setData()`**
```cpp
Node &operator=(const T &d) = delete;
void setData(T d) {
  delete data;
  data = new T(d);
}
```

✅ **解決方法 2：改用 `shared_ptr`**
```cpp
std::shared_ptr<T> data;
data = std::make_shared<T>(d);
```
這樣可以避免 `const` 限制，讓 `Node<T>` 可以順利運作。

---

## **📌 5. 總結**
- **第一層：Node<T> 的 `operator<<`** 負責處理 `data`
- **第二層：T（如 `A`）的 `operator<<`** 負責輸出內容
- **運算子傳遞（Operator Chaining）讓 `std::cout << object;` 適用於不同類別**

這樣的技巧在 **C++ STL、智慧指標、容器類別（如 `std::vector`）** 中經常出現，是進階 C++ 必學的技巧！ 🚀


