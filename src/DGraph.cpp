#include "DGraph.h"

#include "TopologicalSort.h"
#include "Engine.h"
#include "GraphManager.h"
#include "Node.h"

void DGraph::Init() {
  std::cout << "DGraph Init\n";

  // init thread pool
  int maxCount = 18;
  int coreCount = 8;
  int taskQueueLength = 8;
  Policy policy = Discard;
  int liveTime = 2;
  Unit unit = Second;

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

  graph_manager_ = std::make_shared<GraphManager>();
  graph_manager_->SetThreadPool(thread_pool_);
  graph_manager_->Init();
}

void DGraph::CheckCycle() {
  if (!graph_manager_->HasCycle()) {
    std::cout << "### Graph has no cycle ###\n";
  } else {
    std::cout << "### Graph has cycle ###\n";
    exit(0);
  }
}

void DGraph::Run() {
  std::cout << "DGraph Run\n";
  std::cout << "total node count: " << graph_manager_->GetNodeCount()
            << std::endl;
  graph_manager_->Run();
}

void DGraph::Deinit() {
  std::cout << "DGraph Deinit\n";
  graph_manager_->Deinit();
}

bool DGraph::RegisterNode(
    std::shared_ptr<Node>& node,
    std::set<std::shared_ptr<Node>> const& dependency_nodes,
    const std::string node_name) {
  std::cout << "Graph register: " << node_name << std::endl;

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  graph_manager_->AddNode(node);
  return true;
}

bool DGraph::RegisterNode(
    std::shared_ptr<Node>& node,
    std::set<std::shared_ptr<Node>> const& dependency_nodes,
    const std::string node_name,
    int const& loop_count) {
  std::cout << "Graph register: " << node_name << std::endl;

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  node->SetLoopCount(loop_count);
  graph_manager_->AddNode(node);
  return true;
}

void DGraph::TopologicalSort() {
  graph_manager_->TopoSort();
}