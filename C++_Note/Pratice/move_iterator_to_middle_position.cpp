#include <iostream>
#include <iterator>
#include <map>

using namespace std;

int main() {
  map<int, string> map = {
      {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}};

  size_t middle = map.size() / 2;
  auto it = map.begin();
  advance(it, middle);

  cout << it->first << " " << it->second << endl;

  std::map<int, string> map2 = {{1, "one"}, {2, "two"}, {3, "three"}};
  size_t m = map2.size() / 2;
  auto it2 = next(map2.begin(), m);

  cout << it2->first << " " << it2->second << endl;
  return 0;
}
