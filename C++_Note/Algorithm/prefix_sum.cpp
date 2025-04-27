#include <iostream>
#include <vector>
using namespace std;

vector<int> computeprefix_sum(const vector<int> &arr) {
  vector<int> prefix_sum(arr.size() - 1, 0);
  for (int i = 0; i < arr.size(); i++) {
    prefix_sum[i + 1] = prefix_sum[i] + arr[i];
  }
  return prefix_sum;
}

int rangeSum(const vector<int> &vec, int l, int t) {
  return vec[t + 1] - vec[l];
}
int main() {
  vector<int> arr{1, 2, 3, 4, 5};
  vector<int> prefix_sum = computeprefix_sum(arr);
  cout << rangeSum(prefix_sum, 1, 3) << endl;
  return 0;
}
