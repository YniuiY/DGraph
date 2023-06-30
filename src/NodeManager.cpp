#include "NodeManager.h"
#include "Node.h"

void NodeManager::Init() {
  std::cout << "NodeManager Init\n";
}

std::vector<Node*> NodeManager::GetRunAbleNode() {
  std::vector<Node*> run_able_nodes;
  for (auto node : node_set_) {
    if (node->IsRunable()) {
      run_able_nodes.emplace_back(node);
      node->RunBefore();
    }
  }
  return run_able_nodes;
}

int NodeManager::GetNodeCount() {
  return node_set_.size();
}

void NodeManager::AddNode(Node*& node) {
  std::cout << "NodeManager AddNode\n";
  node_set_.emplace(node);
}

void NodeManager::RemoveNode(Node*& node) {
  node_set_.erase(node_set_.find(node));
}