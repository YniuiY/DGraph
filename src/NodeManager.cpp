#include "NodeManager.h"

#include "Node.h"

void NodeManager::Init() { 
  std::cout << "NodeManager Init\n";
}

std::vector<std::shared_ptr<Node>> NodeManager::GetRunAbleNode() {
  std::vector<std::shared_ptr<Node>> run_able_nodes;
  for (auto node : node_set_) {
    if (node->IsRunable()) {
      run_able_nodes.emplace_back(node);
      node->SetNodeState(Node::NodeState::RUNNING);
    }
  }
  return run_able_nodes;
}

int NodeManager::GetNodeCount() { return node_set_.size(); }

void NodeManager::AddNode(std::shared_ptr<Node>& node) {
  node_set_.emplace(node);
}

void NodeManager::RemoveNode(std::shared_ptr<Node>& node) {
  node_set_.erase(node_set_.find(node));
}

bool NodeManager::HasCycle() {
  judgment_cycle_.Init(node_set_); 
  return judgment_cycle_.HasCycle();
}