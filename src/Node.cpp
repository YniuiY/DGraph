#include "Node.h"

Node::Node()
    : left_dep_count_{0},
      node_state_{NodeState::CREATED} {

}

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
  // 节点运行前设置节点状态为running
  node_state_ = NodeState::RUNNING;
}

void Node::RunAfter() {
  // 节点执行完成后，给依赖此节点的后驱节点依赖项减一
  node_state_ = NodeState::RUNNING_DONE;
  for (auto node : right_be_dependency_node_) {
    node->left_dep_count_--;
  }
}

bool Node::IsRunable() {
  bool ret{false};
  // 节点没有running 且 节点没有执行完成 且 前置依赖项为0
  if (node_state_ != NodeState::RUNNING &&
      node_state_ != NodeState::RUNNING_DONE && left_dep_count_ == 0) {
    std::cout << node_name_ << " is run able" << std::endl;
    ret = true;
  }
  return ret;
}

void Node::AddDependencyNodes(std::set<std::shared_ptr<Node>> const& node_set) {
  std::cout << node_name_ << " dependency nodes: ";
  for (auto node : node_set) {
    std::cout << node->GetNodeName() << " ";
    left_dependency_node_.emplace(node);  // 将此节点依赖的前置节点注册进来
    left_dep_count_++;  // 将此节点的依赖项加一，此依赖项归零便可以执行
    indegree_++;

    node->right_be_dependency_node_.emplace(
        this);  // 将依赖此节点的后驱节点注册进来
  }
  std::cout << std::endl;
}

void Node::SetNodeName(std::string const& name) {
  node_name_ = name;
}

std::string Node::GetNodeName() {
  return node_name_;
}

void Node::SetNodeState(NodeState const& state) {
  node_state_ = state;
}

Node::NodeState Node::GetNodeState() {
  return node_state_;
}

std::set<std::shared_ptr<Node>> Node::GetRightNode() {
  return right_be_dependency_node_;
}

int& Node::GetIndegree() {
  return indegree_;
}