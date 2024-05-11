#include "DGraph.h"

#include "TopologicalSort.h"
#include "Engine.h"
#include "GraphManager.h"
#include "Node.h"

void DGraph::Init() {
  std::cout << "DGraph Init\n";
  graph_manager_ = std::make_shared<GraphManager>();
  graph_manager_->Init();
  engine_ = std::make_shared<Engine>();
  engine_->Init(graph_manager_);
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
  engine_->Run();
}

void DGraph::Deinit() {
  std::cout << "DGraph Deinit\n";
  engine_->Deinit();
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

void DGraph::TopologicalSort() {
  graph_manager_->TopoSort();
}