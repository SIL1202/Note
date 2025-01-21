#include <iostream>

using namespace std;

int main() {
  int n, m;
  cin >> n >> m;
  int arr[n][m];
  int arr2[n][m];

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      cin >> arr[i][j];
      arr2[i][j] = 0;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (j + 1 < m)
        arr2[i][j + 1] = max(arr2[i][j] + arr[i][j + 1], arr2[i][j + 1]);
      if (i + 1 < n)
        arr2[i + 1][j] = max(arr2[i][j] + arr[i + 1][j], arr2[i + 1][j]);
    }
  }

  cout << arr2[n - 1][m - 1];
  return 0;
}
