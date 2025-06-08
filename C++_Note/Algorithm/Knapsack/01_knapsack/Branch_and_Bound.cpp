#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct Item {
  int weight, value;
  double ratio;
};

struct Node {
  int level, value, weight;
  double bound;
  bool operator<(const Node &other) const {
    return bound < other.bound; // max-heap
  }
};

double bound(Node u, int n, int W, const vector<Item> &items) {
  if (u.weight >= W)
    return 0;

  double profit_bound = u.value;
  int j = u.level;
  int totweight = u.weight;

  while (j < n && totweight + items[j].weight <= W) {
    totweight += items[j].weight;
    profit_bound += items[j].value;
    j++;
  }

  if (j < n)
    profit_bound += (W - totweight) * items[j].ratio;

  return profit_bound;
}

int knapsackBranchAndBound(int W, vector<Item> &items) {
  sort(items.begin(), items.end(),
       [](Item a, Item b) { return a.ratio > b.ratio; });

  priority_queue<Node> pq;
  Node u, v;
  u.level = 0, u.value = 0, u.weight = 0;
  u.bound = bound(u, items.size(), W, items);
  pq.push(u);

  int maxProfit = 0;
  while (!pq.empty()) {
    u = pq.top();
    pq.pop();

    if (u.bound <= maxProfit)
      continue;

    v.level = u.level + 1;

    // Try including item
    v.weight = u.weight + items[u.level].weight;
    v.value = u.value + items[u.level].value;
    if (v.weight <= W && v.value > maxProfit)
      maxProfit = v.value;
    v.bound = bound(v, items.size(), W, items);
    if (v.bound > maxProfit)
      pq.push(v);

    // Try excluding item
    v.weight = u.weight;
    v.value = u.value;
    v.bound = bound(v, items.size(), W, items);
    if (v.bound > maxProfit)
      pq.push(v);
  }

  return maxProfit;
}

int main() {
  int n, W;
  cin >> n >> W;

  vector<Item> items(n);
  for (int i = 0; i < n; i++)
    cin >> items[i].weight;
  for (int i = 0; i < n; i++)
    cin >> items[i].value;

  for (int i = 0; i < n; i++)
    items[i].ratio = (double)items[i].value / items[i].weight;

  int result = knapsackBranchAndBound(W, items);
  cout << "Maximum value: " << result << endl;

  return 0;
}
