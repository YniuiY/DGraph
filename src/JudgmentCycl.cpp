/**
 * dfs递归的调用栈，表示的是“当前”正在遍历的有向图的路径。
 * 将Node入栈onStack表示节点在栈中，出栈则将Node从栈中删除。
 * 从dfs的for循环出来，表明此节点的所有邻接节点都被访问过了，所以这个节点应该从dfs调用栈出栈。
 * 
 * 如果一个节点被访问过，且再次被访问时存在与调用栈中，意味着遍历沿着环走了一遍并再次访问到这个节点，这个节点是环的一部分。
 * 如果一个节点被访问过，且再次被访问时存在与调用栈中，意味着遍历沿着环走一遍并再次访问到这个节点，这个节点是环的一部分。
 * 如果不存在以上情况则无环。
 */

#include "JudgmentCycle.h"
#include <Node.h>
#include <queue>

JudgmentCycle::JudgmentCycle(): is_cycle_{false}, marked_{nullptr}, on_stack_{nullptr} {

}

JudgmentCycle::~JudgmentCycle() {
  std::cout << "~JudgmentCycle()\n";
}

void JudgmentCycle::Init(std::set<std::shared_ptr<Node>> const& node_set) {
  adjs_ = node_set;
}

bool JudgmentCycle::HasCycle() {
  check_cycle();
  if (is_cycle_) {
    CycleNodes();
  } else {
    std::cout << "### This graph is DAG ###\n";
    std::cout << "### Graph Order:";
    std::stack<std::shared_ptr<Node>> order = node_order_;
    while (!order.empty()) {
      std::cout <<  " " << order.top()->GetNodeName();
      order.pop();
    }
    std::cout << " ###\n";
  }
  return is_cycle_;
}

void JudgmentCycle::check_cycle() {
  if (!adjs_.empty()) {
    // 单纯的给dfs一个节点开始递归，会漏掉独立的节点，所以用for循环遍历adjs中所有节点交给dfs
    // dfs(*adjs_.begin());
    for (auto node : adjs_) {
      if (marked_.find(node) == marked_.end()) {
        dfs(node);
      }
    }
  }
}

void JudgmentCycle::dfs(std::shared_ptr<Node> const& node) {
  marked_.emplace(node);
  on_stack_.emplace(node);
  std::cout << "marked node: " << node->GetNodeName() << std::endl;

  for (auto right_node : node->GetRightNode()) {
    if (is_cycle_) {
      return;
    } else if (marked_.find(right_node) == marked_.end()) { //节点未被遍历过
      edge_to_[right_node->GetNodeName()] = node->GetNodeName();
      std::cout << "edge_to[" << right_node->GetNodeName() << "]: " << node->GetNodeName() << std::endl;
      dfs(right_node);
    } else if (on_stack_.find(right_node) != on_stack_.end()) { // 节点被遍历过且目前存在与dfs遍历调用栈中
      // 下一个节点在调用栈中
      is_cycle_ = true;

      /**
       * @todo 汇总所有成环节点
       */
      for (auto now_node_name = node->GetNodeName();
           now_node_name != right_node->GetNodeName();
           now_node_name = edge_to_[now_node_name]) {
        cycle_node_.push(now_node_name);
      }
      cycle_node_.push(right_node->GetNodeName());
      cycle_node_.push(node->GetNodeName());
    }
  }

  /// @brief 逆后续排序结果就是拓扑排序结果（后序和逆后续节点加入顺序相同，但逆后续排序入栈，后序排序入队列）
  node_order_.push(node); 
  on_stack_.erase(on_stack_.find(node));
}

void JudgmentCycle::CycleNodes() {
  /**
   * @todo 打印所有成环节点的名字
   */
  std::cout << "### Cycle Nodes:";
  while (!cycle_node_.empty()) {
    std::cout << " " << cycle_node_.top();
    cycle_node_.pop();
  }
  std::cout << " ###\n";
}

std::stack<std::shared_ptr<Node>> JudgmentCycle::GetOrderNodeStack() {
  if (is_cycle_) {
    std::cout << "有环图无法对拓扑排序" << std::endl;
    throw std::runtime_error("cycle graph don't have order");
  }
  return node_order_;
}

void JudgmentCycle::GetBfsFrontOrder() {
  bfs(*adjs_.begin());
}

/**
 * Create by Codegeex
 */
void JudgmentCycle::bfs(std::shared_ptr<Node> const& node) {
  // 记录BFS的顺序
  std::vector<std::string> bfs_front_order;
  // 队列，用于BFS
  std::queue<std::shared_ptr<Node>> queue;
  // 将根节点放入队列
  queue.push(node);
  // 当队列不为空时，循环
  while (!queue.empty()) {
    // 取出队列中的节点
    auto now_node = queue.front();
    // 将节点放入BFS顺序中
    bfs_front_order.push_back(now_node->GetNodeName());
    // 将节点从队列中弹出
    queue.pop();
    // 遍历节点的右子节点
    for (auto const& right_node : now_node->GetRightNode()) {
      // 如果右子节点不在栈中，则将其加入栈中
      if (on_stack_.find(right_node) == on_stack_.end()) {
        on_stack_.insert(right_node);
        queue.push(right_node);
      }
    }
  }

  // 打印BFS的顺序
  std::cout << "### BFS Front Order:";
  for (auto const& node : bfs_front_order) {
    std::cout << node << " ";
  }
}