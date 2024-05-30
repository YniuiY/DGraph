#include "Node.h"

#include "ParamManager/ParamManager.h"
#include "Utils/TimeUtil.h"
#include "thread_pool.hpp"

Node::Node()
    : left_dep_count_{0},
      loop_count_{1},
      node_state_{NodeState::CREATED} {

}

Node::~Node() {
  std::cout << "~Node(): " << node_name_ << std::endl;
}

void Node::Init() {
  node_state_ = NodeState::INITED;
}

void Node::Process() {
  RunBefore();
  for (int i = 0; i < loop_count_; i++) {
    run();
  }
  RunAfter();
}

void Node::run() {
  // 不同的节点重新不同的run实现
  std::cout << "Node run\n";
}

void Node::RunBefore() {
  // 节点运行前设置节点状态为running
  node_state_ = NodeState::RUNNING;
  std::cout << "Node: " << node_name_ << " run before" << std::endl;
}

void Node::RunAfter() {
  node_state_ = NodeState::RUNNING_DONE;
  // 节点执行完成后，给依赖此节点的后驱节点依赖项减一
  std::cout << "Node: " << node_name_ << " run after" << std::endl;

  // for (auto node : right_be_dependency_node_) {
  //   node->IndegreeDecrease(); // TODO:给indegree的加减加锁
  // }
  // 运行结束后重置本节点入度
  indegree_reset();

  // 运行结束后重置本节点状态为初始状态
  // 节点状态为初始状态，表示此节点可以被调度
  node_state_ = NodeState::INITED;
}

bool Node::IsRunable() {
  bool ret{false};
  // 节点前置依赖项为0 且 节点状态为初始状态，表示此节点可以被调度
  if (indegree_ == 0 && node_state_ == NodeState::INITED) {
    std::cout << node_name_ << " is run able" << std::endl;
    ret = true;
    node_state_ = NodeState::RUNNING_WAITING;
  }
  return ret;
}

void Node::AddDependencyNodes(std::set<Node*> const& node_set) {
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
  std::cout << " indegree: " << indegree_ << std::endl;
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

std::set<Node*> Node::GetRightNode() {
  return right_be_dependency_node_;
}

std::set<Node*> Node::GetLeftNode() {
  return left_dependency_node_;
}

int Node::GetIndegree() {
  std::lock_guard<std::mutex> lock(indegree_mutex_);
  return indegree_;
}

int Node::GetIndegreeDecrease() {
  std::lock_guard<std::mutex> lock(indegree_mutex_);
  std::cout << "Node: " << node_name_ << " indegree decrease: " << indegree_ - 1 << std::endl;
  return --indegree_;
}

int& Node::GetLeftDepCount() {
  return left_dep_count_;
}

void Node::SetNodeType(NodeType type) {
  node_type_ = type;
}

Node::NodeType Node::GetNodeType() {
  return node_type_;
}

void Node::SetLoopCount(int const& loop_count) {
  loop_count_ = loop_count;
}

int Node::GetLoopCount() {
  return loop_count_;
}

void Node::SetThreadPool(std::shared_ptr<ThreadPool> const& tp) {
  tp_ = tp;
}

void Node::IndegreeDecrease() {
  std::lock_guard<std::mutex> lock(indegree_mutex_);
  --indegree_;
}

void Node::indegree_reset() {
  std::lock_guard<std::mutex> lock(indegree_mutex_);
  indegree_ = static_left_dep_count_;
}