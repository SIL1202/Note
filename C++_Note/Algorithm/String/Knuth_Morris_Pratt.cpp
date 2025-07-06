// string matching algorithm
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> LPS(string);  // build lps table
void KMP(string, string); // string matching

// KMP concise version, can use in competition
void KMP_Concise(string, string);

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
  cout << '\n';
  KMP_Concise(s, pattern);
  return 0;
}

void KMP_Concise(string s, string p) {
  int n = s.length();
  int m = p.length();

  // build lps table
  vector<int> lps(m);
  for (int i = 1, j = 0; i < m;) {
    if (p[i] == p[j])
      lps[i++] = ++j;
    else if (j != 0)
      j = lps[j - 1];
    else
      lps[i++] = 0;
  }

  // string matching
  int count = 0;
  for (int i = 0, j = 0; i < n;) {
    if (s[i] == p[j])
      ++i, ++j;
    if (j == m)
      ++count, j = lps[j - 1];
    else if (i < n && s[i] != p[j])
      j ? j = lps[j - 1] : ++i;
  }
  cout << "Count from concise version: " << count << '\n';
}
