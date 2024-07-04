#include "GraphManager.h"

#include "Node.h"
#include "Engine.h"
#include "thread_pool.hpp"
#include "TopologicalSort.h"
#include "JudgmentCycle.h"

GraphManager::GraphManager(): engine_{std::make_shared<Engine>()},
                              judgment_cycle_{std::make_shared<JudgmentCycle>()},
                              topo_sort_{nullptr} {
  dgraph::Logger::GetLogger()->info("GraphManager()");
}

GraphManager::GraphManager(EngineType const& engin_type): judgment_cycle_{std::make_shared<JudgmentCycle>()},
                              topo_sort_{nullptr} {
  switch (engin_type)
  {
  case EngineType::GRAPH_ENGINE :
    /* code */
    engine_ = std::make_shared<Engine>();
    break;
  
  case EngineType::REGION_ENGINE :
    /* code */
    engine_ = std::make_shared<Engine>(true);
    break;

  default:
    break;
  }
  dgraph::Logger::GetLogger()->info("GraphManager()");
}

GraphManager::~GraphManager() {
  dgraph::Logger::GetLogger()->info("~GraphManager()");
  for (auto node: node_set_) {
    if (node != nullptr) {
      delete node;
      node = nullptr;
    }
  }
}

void GraphManager::Init() {
  dgraph::Logger::GetLogger()->info("GraphManager Init()");
  engine_->Init(node_set_, thread_pool_);
  for (auto node: node_set_) {
    node->SetThreadPool(thread_pool_);
    node->Init();
  }
  dgraph::Logger::GetLogger()->info("GraphManager Init() Done");
}

void GraphManager::Run() {
  dgraph::Logger::GetLogger()->info("GraphManager Run()");
  engine_->Run();
  dgraph::Logger::GetLogger()->info("GraphManager Run() Done");
}

void GraphManager::Deinit() {
  engine_->Deinit();
}

void GraphManager::SetThreadPool(std::shared_ptr<ThreadPool> const& thread_pool) {
  thread_pool_ = thread_pool;
}

int GraphManager::GetNodeCount() { return node_set_.size(); }

void GraphManager::AddNode(Node*& node) {
  node_set_.emplace(node);
}

void GraphManager::RemoveNode(Node*& node) {
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