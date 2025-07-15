#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  string text, pattern;
  cin >> text >> pattern;

  string combine =
      pattern + "$" + text; // let the pattern be the prefix of the text
  int len = combine.length();
  vector<int> z(len);

  int l = 0, r = 0;
  for (int i = 1; i < len; ++i) {
    if (i <= r) {
      z[i] = min(r - i + 1, z[i - l]);
    }
    while (i + z[i] < len && combine[z[i]] == combine[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }

  // print out the positions
  for (int i = pattern.length() + 1; i < len; ++i) {
    if (z[i] == pattern.length()) {
      cout << "Pattern found at index: " << (i - pattern.length() - 1) << '\n';
    }
  }

  return 0;
}

// abc$xabcabyabc
// 00000300200300
