#include "DGraph.h"

#include "TopologicalSort.h"
#include "Engine.h"
#include "GraphManager.h"
#include "Node.h"
#include "thread_pool.hpp"

DGraph::DGraph(): graph_manager_{std::make_shared<GraphManager>()} {

}

DGraph::~DGraph() {
  std::cout << "~DGraph()\n";
}

void DGraph::Init() {
  std::cout << "DGraph Init\n";

  // init thread pool
  int maxCount = 20;
  int coreCount = 18;
  int taskQueueLength = 200;
  Policy policy = Discard;
  int liveTime = 20;
  ThreadPool::Unit unit = ThreadPool::Unit::Second;

  std::cout << "\n**************************************************"
            << "\nInit thread pool:\nmax thread count: " << maxCount
            << "\ncore thread count: " << coreCount
            << "\ntask queu length: " << taskQueueLength
            << "\npolicy: " << policy
            << "\nempty thread live time: " << liveTime
            << "\nlive time unit: " << unit
            << "\n*************************************************\n"
            << std::endl;
  thread_pool_ = std::make_shared<ThreadPool>(
      maxCount, coreCount, taskQueueLength, policy, liveTime, unit);

  graph_manager_->SetThreadPool(thread_pool_);
  graph_manager_->Init();
  check_cycle();
  topological_sort();
  std::cout << "DGraph Init Done\n";
}

void DGraph::Run() {
  std::cout << "DGraph Running\n";
  std::cout << "total node count: " << graph_manager_->GetNodeCount()
            << std::endl;
  std::cout << "\n\n\n****************************** ******* *********************************\n";
  std::cout << "****************************** Running *********************************\n";
  std::cout << "****************************** ******* *********************************\n\n\n";
  graph_manager_->Run();
  std::cout << "DGraph Running Done\n";
}

void DGraph::Deinit() {
  std::cout << "DGraph Deinit\n";
  graph_manager_->Deinit();
}

bool DGraph::RegisterNode(
    Node*& node,
    std::set<Node*> const& dependency_nodes,
    const std::string node_name) {
  std::cout << "Graph register: " << node_name << std::endl;

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
  std::cout << "Graph register: " << node_name << std::endl;

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  node->SetLoopCount(loop_count);
  graph_manager_->AddNode(node);
  return true;
}

void DGraph::check_cycle() {
  if (!graph_manager_->HasCycle()) {
    std::cout << "### Graph has no cycle ###\n";
  } else {
    std::cout << "### Graph has cycle ###\n";
    throw std::runtime_error("Graph has cycle");
  }
}

void DGraph::topological_sort() {
  graph_manager_->TopoSort();
}