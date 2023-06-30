#include "Node.h"

Node::Node() : left_dep_count_{0}, running_done_{false}, running_{false} {}

void Node::Process() {
    RunBefore();
    run();
    RunAfter();
  }

  void Node::run() {
    // 不同的节点重新不同的run实现
    std::cout << "Node run\n";
  }

  void Node::RunBefore() {
    running_ = true;
    running_done_ = false;
  }

  void Node::RunAfter() {
    running_done_ = true;
    running_ = false;
    for (auto node : right_be_dependency_node_) {
      node->left_dep_count_--;
    }
  }

  bool Node::IsRunable() {
    bool ret{false};
    if (!running_ && !running_done_ && left_dep_count_ == 0) {
      std::cout << node_name_ << " is run able" << std::endl;
      ret = true;
    }
    return ret;
  }

void Node::AddDependencyNodes (std::set<Node*>const& node_set) {
  std::cout << "Node AddDependencyNodes\n";
  for (auto node : node_set) {
    std::cout << node->GetNodeName() << " ";
    left_dependency_node_.emplace(node);
    left_dep_count_++;

    node->right_be_dependency_node_.emplace(this);
  }
  std::cout << std::endl;
}

void Node::SetNodeName(std::string const& name) {
  node_name_ = name;
}

std::string Node::GetNodeName() {
  return node_name_;
}