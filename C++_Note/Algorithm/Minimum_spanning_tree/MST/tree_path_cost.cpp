// compute path cost using DFS and BFS
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

struct TreeNode {
  int id;
  std::vector<std::pair<TreeNode *, int>> children; // (child_node, edge_weight)
};

int computePathCostDFS(TreeNode *root, TreeNode *target) {
  if (!root || !target)
    return -1; // invaild input

  std::function<bool(TreeNode *, int &, int)> dfs =
      [&](TreeNode *node, int &cost, int currentSum) {
        if (node == target) {
          cost = currentSum;
          return true;
        }

        for (auto [child, weight] : node->children) {
          if (dfs(child, cost, currentSum + weight)) {
            return true;
          }
        }
        return false;
      };

  int cost = 0;
  dfs(root, cost, 0);
  return cost;
}

int computePathCostBFS(TreeNode *root, TreeNode *target) {
  if (!root || !target)
    return -1;

  std::queue<std::pair<TreeNode *, int>> q; // (node, current_cost)
  q.push({root, 0}); // initialize, root node and cost = 0.

  while (!q.empty()) {
    auto [node, current_cost] = q.front();
    q.pop();

    if (node == target)
      return current_cost; // find target return current cost
    for (auto &[child, weight] : node->children) {
      q.push({child, weight + current_cost});
    }
  }
  return -1; // target doesn't exist
}

int main() {
  TreeNode F{6, {}}; // target
  TreeNode E{5, {}};
  TreeNode D{4, {}};
  TreeNode C{3, {{&E, 1}, {&F, 4}}}; // C -> E (weight=1), C -> F (weight=4)
  TreeNode B{2, {{&D, 1}}};          // B -> D (weight=1)
  TreeNode A{1, {{&B, 3}, {&C, 2}}}; // A -> B (weight=3), A -> C (weight=2)

  std::cout << "Cost from A to F: " << computePathCostDFS(&A, &F)
            << std::endl; // output 6 (2+4)

  std::cout << "Cost from A to F: " << computePathCostBFS(&A, &F)
            << std::endl; // output 6 (2+4)

  return 0;
}
