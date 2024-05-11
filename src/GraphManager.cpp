#include "GraphManager.h"

#include "Node.h"

GraphManager::GraphManager() {
}

GraphManager::~GraphManager() {}

void GraphManager::Init() { 
  std::cout << "GraphManager Init\n";
}

/**
 * 根据拓扑排序的顺序，依次检查节点是否可执行
 */
std::vector<std::shared_ptr<Node>> GraphManager::GetRunAbleNode() {
  std::vector<std::shared_ptr<Node>> run_able_nodes;
  // 可以按照DAG一直运行
  for (auto node : order_node_queue_) {
    if (node->IsRunable()) {
      // std::cout << "GraphManager GetRunAbleNode " << node->GetNodeName() << std::endl;
      run_able_nodes.emplace_back(node);
    }
  }

  return run_able_nodes;
}

int GraphManager::GetNodeCount() { return node_set_.size(); }

void GraphManager::AddNode(std::shared_ptr<Node>& node) {
  node_set_.emplace(node);
  
}

void GraphManager::RemoveNode(std::shared_ptr<Node>& node) {
  node_set_.erase(node_set_.find(node));
}

bool GraphManager::HasCycle() {
  bool ret = false;
  judgment_cycle_.Init(node_set_); 
  // judgment_cycle_.GetBfsFrontOrder();
  ret = judgment_cycle_.HasCycle();
  // order_node_stack_ = judgment_cycle_.GetOrderNodeStack();

  return ret;
}

void GraphManager::TopoSort() {
  topo_sort_ = std::make_shared<TopologicalSort>(node_set_);
  order_node_queue_ = topo_sort_->Sort();
  order_node_stack_ = topo_sort_->DfsSort();
  topo_sort_->PrintOrder();
}