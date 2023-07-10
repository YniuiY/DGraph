#include "JudgmentCycle.h"
#include <Node.h>

JudgmentCycle::JudgmentCycle(): is_cycle_{false}, marked_{nullptr}, on_stack_{nullptr} {

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
    while (!node_order_.empty()) {
      std::cout <<  " " << node_order_.top()->GetNodeName();
      node_order_.pop();
    }
    std::cout << " ###\n";
  }
  return is_cycle_;
}

void JudgmentCycle::check_cycle() {
  if (!adjs_.empty()) {
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
  node_order_.push(node); // 逆后续排序结果就是拓扑排序结果
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

std::stack<std::shared_ptr<Node>> JudgmentCycle::GetOrder() {
  return node_order_;
}