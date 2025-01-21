#include <iostream>
#include <string>

int main() {
  std::string s("hello world");
  std::string substr("ld");

  if (s.substr(s.size() - substr.size()) == substr) { // 如果字串最後符合的話
    std::cout << s.substr(s.size() - substr.size()) << std::endl;
    std::cout << s + "s" << std::endl;
  }

  auto it = s.find(substr);
  if (it != std::string::npos) { // 如果沒有找到就會回傳std::string::npos
    std::cout << "found!\n";
  } else
    std::cout << "not found\n";
  return 0;
}
