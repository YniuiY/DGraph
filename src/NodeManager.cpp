#include "NodeManager.h"

#include "Node.h"

NodeManager::NodeManager() {
}

NodeManager::~NodeManager() {}

void NodeManager::Init() { 
  std::cout << "NodeManager Init\n";
}

/**
 * 根据拓扑排序的顺序，依次检查节点是否可执行
 */
std::vector<std::shared_ptr<Node>> NodeManager::GetRunAbleNode() {
  std::vector<std::shared_ptr<Node>> run_able_nodes;
  while (!order_node_queue_.empty()) {
    auto node = order_node_queue_.front();
    if (node->IsRunable()) {
      std::cout << "NodeManager GetRunAbleNode " << node->GetNodeName() << std::endl;
      run_able_nodes.emplace_back(node);
      order_node_queue_.pop();
    } else {
      break;
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
  bool ret = false;
  judgment_cycle_.Init(node_set_); 
  // judgment_cycle_.GetBfsFrontOrder();
  ret = judgment_cycle_.HasCycle();
  // order_node_stack_ = judgment_cycle_.GetOrderNodeStack();

  return ret;
}

void NodeManager::TopoSort() {
  topo_sort_ = std::make_shared<TopologicalSort>(node_set_);
  order_node_queue_ = topo_sort_->Sort();
  order_node_stack_ = topo_sort_->DfsSort();
  topo_sort_->PrintOrder();
}