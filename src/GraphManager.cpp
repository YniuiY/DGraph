#include "GraphManager.h"

#include "Node.h"
#include "Engine.h"
#include "threadpool/ThreadPool.hpp"
#include "TopologicalSort.h"
#include "JudgmentCycle.h"

GraphManager::GraphManager(): engine_{std::make_shared<Engine>()} {

}

GraphManager::~GraphManager() {}

void GraphManager::Init() { 
  std::cout << "GraphManager Init\n";
  engine_->Init(node_set_, thread_pool_);
  std::cout << "GraphManager Init Done\n";
}

void GraphManager::Run() {
  engine_->Run();
}

void GraphManager::Deinit() {
  engine_->Deinit();
}

void GraphManager::SetThreadPool(std::shared_ptr<ThreadPool> const& thread_pool) {
  thread_pool_ = thread_pool;
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
  judgment_cycle_->Init(node_set_); 
  // judgment_cycle_.GetBfsFrontOrder();
  ret = judgment_cycle_->HasCycle();
  // order_node_stack_ = judgment_cycle_.GetOrderNodeStack();

  return ret;
}

void GraphManager::TopoSort() {
  topo_sort_ = std::make_shared<TopologicalSort>(node_set_);
  order_node_queue_ = topo_sort_->Sort();
  order_node_stack_ = topo_sort_->DfsSort();
  topo_sort_->PrintOrder();
}