#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> LPS(string pattern) {
  int n = pattern.size();
  vector<int> lps(n);
  int j = 0, i = 1;
  while (i < n) {
    if (pattern[i] == pattern[j]) {
      ++j;
      lps[i] = j;
      ++i;
    } else {
      if (j != 0)
        j = lps[j - 1];
      else {
        lps[i] = 0;
        ++i;
      }
    }
  }
  return lps;
}

void KMP(string s, string pattern) {
  int n = s.length();
  int m = pattern.length();
  vector<int> lps = LPS(pattern);
  int i, j;
  i = j = 0;

  while (i < n) {
    if (s[i] == pattern[j]) {
      ++i;
      ++j;
    }
    if (j == m) {
      cout << "Pattern found at index: " << i - j << '\n';
      j = lps[j - 1];
    } else {
      if (i < n && s[i] != pattern[j]) {
        if (j != 0)
          j = lps[j - 1];
        else
          ++i;
      }
    }
  }
}

int main() {
  string s, pattern;
  cin >> s >> pattern;
  KMP(s, pattern);
  return 0;
}
