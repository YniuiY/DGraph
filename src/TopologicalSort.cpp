/**
 * 拓扑排序参考文献：
 * https://blog.csdn.net/lisonglisonglisong/article/details/45543451
 */

#include "TopologicalSort.h"

// Constructor
TopologicalSort::TopologicalSort(std::set<std::shared_ptr<Node>> adjs) {
  adjs_ = adjs;
}

std::vector<std::shared_ptr<Node>> TopologicalSort::Sort() {
  /// @brief 存储入度为0的节点
  std::queue<std::shared_ptr<Node>> queue;
  /// @brief 将邻接表中入度为零的节点加入队列
  for (auto node : adjs_) {
    if (node->GetIndegree() == 0) {
      queue.push(node);
    }
  }

  /**
   * 1. 入度为零的节点加入拓扑排序结果
   * 2. 将此节点的后驱节点入度减一
   * 3. 如果后驱节点入度为零则入队列queue
   * 4. 循环1-3，直到图中不存在入度为零的节点
   */
  while (!queue.empty()) {
    auto node = queue.front();
    queue.pop();
    topological_order_.push_back(node);

    for (auto node : node->GetRightNode()) {
      if (--node->GetIndegree() == 0) {
        queue.push(node);
      }
    }
  }

  /**
   * 在环上的节点入度不可能减为0，
   * 退出上面while循环的时候，不能遍历全部的节点
   * 所以topological_order_的元素少于adjs_的元素数，就可以证明有环
   */
  if (topological_order_.size() != adjs_.size()) {
    std::cout << "topological order node: " << topological_order_.size() << ", adjs node: " << adjs_.size() << std::endl;
    throw std::runtime_error("There is a cycle in the graph.");
  } else {
    return topological_order_;
  }
}

/**
 * DFS做后续遍历，将遍历结果入栈（逆后续遍历）
 * 结果就是拓扑排序
 * 但是实践发现，DFS的拓扑排序结果不如上面的排序直观
 */
std::stack<std::shared_ptr<Node>> TopologicalSort::DfsSort() {
  for (auto node : adjs_) {
    if (marked_.find(node) == marked_.end()) {
      dfs(node);
    }
  }

  if (!has_cycle_) {
    return reverse_post_order_;
  } else {
    throw std::runtime_error("There is a cycle in the graph.");
  }
}

void TopologicalSort::dfs(std::shared_ptr<Node> node) {
  marked_.insert(node);
  on_stack_.emplace(node);

  for (auto node : node->GetRightNode()) {
    if (on_stack_.find(node) != on_stack_.end()) {
      has_cycle_ = true;
      return; // 这里直接return，因为如果有环，就不需要继续遍历了
    }
    if (marked_.find(node) == marked_.end()) {
      dfs(node);
    }
  }

  reverse_post_order_.push(node);
  on_stack_.erase(on_stack_.find(node));
}

void TopologicalSort::PrintOrder() {
  std::vector<std::shared_ptr<Node>> queue{topological_order_};
  std::cout << "Topological order: ";
  for (auto node : topological_order_) {
    std::cout << node->GetNodeName() << " ";
  }
  std::cout << std::endl;

  std::cout << "\n******************************\n\n";
  std::stack<std::shared_ptr<Node>> stack{reverse_post_order_};
  std::cout << "Reverse post order: ";
  while (!stack.empty()) {
    auto node = stack.top();
    stack.pop();
    std::cout << node->GetNodeName() << " ";
  }
  std::cout << std::endl;
}