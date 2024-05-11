#include "Node.h"

#include "ParamManager/ParamManager.h"
#include "Utils/TimeUtil.h"

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
  for (auto node : right_be_dependency_node_) {
    node->left_dep_count_--;
  }
  // 运行结束后重置本节点入度
  left_dep_count_ = static_left_dep_count_;
  std::cout << node_name_ << " reset left_dep_count_: " << left_dep_count_ << std::endl;
  node_state_ = NodeState::RUNNING_DONE;
}

bool Node::IsRunable() {
  bool ret{false};
  // 节点前置依赖项为0 且 不是正在执行状态 且 不是准备执行状态 
  if (left_dep_count_ == 0 &&
      node_state_ != NodeState::RUNNING &&
      node_state_ != NodeState::RUNNING_WAITING) {
    std::cout << node_name_ << " is run able" << std::endl;
    ret = true;
    node_state_ = NodeState::RUNNING_WAITING;
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
    static_left_dep_count_++;

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

std::set<std::shared_ptr<Node>> Node::GetLeftNode() {
  return left_dependency_node_;
}

int& Node::GetIndegree() {
  return indegree_;
}