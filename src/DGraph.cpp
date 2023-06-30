#include "DGraph.h"

void DGraph::Init() {
  std::cout << "DGraph Init\n";
  node_manager_.Init();
  engine_.Init(&node_manager_);
}

void DGraph::Run() {
  std::cout << "DGraph Run\n";
  std::cout << "total node count: " << node_manager_.GetNodeCount() << std::endl;
  engine_.Run();
}

void DGraph::Deinit () {

}

bool DGraph::RegisterNode(Node*& node, std::set<Node*>const& dependency_nodes, const std::string node_name) {
  std::cout << "DGraph RegisterNode, Node: " << node_name << std::endl;

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  node_manager_.AddNode(node);
  return true;
}