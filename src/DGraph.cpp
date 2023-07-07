#include "DGraph.h"

void DGraph::Init() {
  std::cout << "DGraph Init\n";
  node_manager_ = std::make_shared<NodeManager>();
  node_manager_->Init();
}

void DGraph::CheckCycle() {
  if (!node_manager_->HasCycle()) {
    engine_.Init(node_manager_);
  } else {
    std::cout << "Graph has cycle\n";
    exit(0);
  }
}

void DGraph::Run() {
  std::cout << "DGraph Run\n";
  std::cout << "total node count: " << node_manager_->GetNodeCount()
            << std::endl;
  engine_.Run();
}

void DGraph::Deinit() {}

bool DGraph::RegisterNode(
    std::shared_ptr<Node>& node,
    std::set<std::shared_ptr<Node>> const& dependency_nodes,
    const std::string node_name) {
  std::cout << "Graph register: " << node_name << std::endl;

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  node_manager_->AddNode(node);
  return true;
}