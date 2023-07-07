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
    std::cout << "### This grahp is DAG ###\n";
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
    } else if (marked_.find(right_node) == marked_.end()) {
      dfs(right_node);
    } else if (on_stack_.find(right_node) != on_stack_.end()) {
      // 下一个节点在调用栈中
      is_cycle_ = true;

      /**
       * @todo 汇总所有成环节点
       */
    }
  }
  on_stack_.erase(on_stack_.find(node));
}

void JudgmentCycle::CycleNodes() {
  /**
   * @todo 打印所有成环节点的名字
   */
}