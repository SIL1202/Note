#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

int maxValue = 0;

int RemainingValue(int i, int n, int W, int currentW, vector<int> &weights,
                   vector<int> &values) {
  int total = 0;
  for (int j = i; j < n; j++) {
    if (currentW + weights[j] <= W) {
      currentW += weights[j];
      total += values[j];
    } else
      break;
  }
  return total;
}

void Backtrack(int i, int n, int W, int currentW, int currentV,
               vector<int> &weights, vector<int> &values) {
  if (currentW > W)
    return;
  if (i == n) {
    maxValue = max(maxValue, currentV);
    return;
  }

  int remaining = RemainingValue(i, n, W, currentW, weights, values);
  if (currentV + remaining <= maxValue)
    return;

  Backtrack(i + 1, n, W, currentW + weights[i], currentV + values[i], weights,
            values);
  Backtrack(i + 1, n, W, currentW, currentV, weights, values);
}

int main() {
  int n, x;
  cin >> n >> x;
  vector<int> weights(n), values(n);
  for (int &w : weights)
    cin >> w;
  for (int &v : values)
    cin >> v;

  vector<pair<double, int>> ratio;
  for (int i = 0; i < n; i++)
    ratio.push_back({(double)values[i] / weights[i], i});
  sort(ratio.rbegin(), ratio.rend());

  vector<int> sortedW, sortedV;
  for (auto &index : ratio) {
    sortedW.push_back(weights[index.second]);
    sortedV.push_back(values[index.second]);
  }

  Backtrack(0, n, x, 0, 0, sortedW, sortedV);
  cout << maxValue << '\n';
  return 0;
}
