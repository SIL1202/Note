#include <functional>
#include <iostream>
using namespace std;

// 定義 process 函數，接受一個操作函數和兩個整數作為參數
void process(function<int(int, int)> func, int a, int b) {
  cout << func(a, b) << endl;
}

int main() {
  // 使用 lambda 表達式定義不同的操作
  auto add = [](int a, int b) { return a + b; };
  auto subtract = [](int a, int b) { return a - b; };
  auto multiply = [](int a, int b) { return a * b; };
  auto divide = [](int a, int b) { return a / b; };

  // 使用 process 函數執行不同的操作
  process(add, 5, 6);
  process(subtract, 5, 6);
  process(multiply, 5, 6);
  process(divide, 5, 6);

  // 根據用戶選擇設置操作函數
  int choice;
  function<int(int, int)> optionSelect;
  cout << "Select operation:\n1-Add\n2-Subtract\n3-Multiply\n4-Divide\n";
  while (cin >> choice) {
    switch (choice) {
    case 1:
      optionSelect = add;
      break;
    case 2:
      optionSelect = subtract;
      break;
    case 3:
      optionSelect = multiply;
      break;
    case 4:
      optionSelect = divide;
      break;
    default:
      cout << "Invalid choice\n";
      return 0;
    }
    // 執行用戶選擇的操作
    cout << optionSelect(20, 4) << endl << endl;
    cout << "Select operation:\n1-Add\n2-Subtract\n3-Multiply\n4-Divide\n";
  }
  return 0;
}
