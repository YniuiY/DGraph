#include "DGraph.h"

#include "TopologicalSort.h"
#include "Engine.h"
#include "GraphManager.h"
#include "Node.h"
#include "thread_pool.hpp"

DGraph::DGraph(): graph_manager_{std::make_shared<GraphManager>()} {
  dgraph::Logger::GetLogger()->debug("DGraph()");
}

DGraph::~DGraph() {
  dgraph::Logger::GetLogger()->debug("~DGraph()");
}

void DGraph::Init() {
  // init thread pool
  int maxCount = 20;
  int coreCount = 18;
  int taskQueueLength = 200;
  Policy policy = Discard;
  int liveTime = 20;
  ThreadPool::Unit unit = ThreadPool::Unit::Second;

  dgraph::Logger::GetLogger()->debug(
      "Init thread pool:\nmax thread count: " + std::to_string(maxCount) +
      ", core thread count: " + std::to_string(coreCount) +
      ", task queu length: " + std::to_string(taskQueueLength) +
      ", policy: " + std::to_string(policy) +
      ", empty thread live time: " + std::to_string(liveTime) +
      ", live time unit: " + std::to_string(unit));
  thread_pool_ = std::make_shared<ThreadPool>(
      maxCount, coreCount, taskQueueLength, policy, liveTime, unit);

  graph_manager_->SetThreadPool(thread_pool_);
  graph_manager_->Init();
  check_cycle();
  topological_sort();
  dgraph::Logger::GetLogger()->debug("DGraph Init Done");
}

void DGraph::Run() {
  dgraph::Logger::GetLogger()->debug("DGraph Running");
  dgraph::Logger::GetLogger()->debug("total node count: " + std::to_string(graph_manager_->GetNodeCount()));
  std::cout << "\n\n\n****************************** ******* *********************************\n";
  std::cout << "****************************** Running *********************************\n";
  std::cout << "****************************** ******* *********************************\n\n\n";
  graph_manager_->Run();
  dgraph::Logger::GetLogger()->debug("DGraph Running Done");
}

void DGraph::Deinit() {
  dgraph::Logger::GetLogger()->debug("DGraph Deinit");
  graph_manager_->Deinit();
}

bool DGraph::RegisterNode(
    Node*& node,
    std::set<Node*> const& dependency_nodes,
    const std::string node_name) {
  dgraph::Logger::GetLogger()->debug("Graph register: " + node_name);

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  graph_manager_->AddNode(node);
  return true;
}

bool DGraph::RegisterNode(
    Node*& node,
    std::set<Node*> const& dependency_nodes,
    const std::string node_name,
    int const& loop_count) {
  dgraph::Logger::GetLogger()->debug("Graph register: " + node_name);

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  node->SetLoopCount(loop_count);
  graph_manager_->AddNode(node);
  return true;
}

void DGraph::check_cycle() {
  if (!graph_manager_->HasCycle()) {
    dgraph::Logger::GetLogger()->debug("### Graph has no cycle ###");
  } else {
    dgraph::Logger::GetLogger()->error("### Graph has cycle ###");
    throw std::runtime_error("Graph has cycle");
  }
}

void DGraph::topological_sort() {
  graph_manager_->TopoSort();
}