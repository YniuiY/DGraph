#include "Region/Region.h"

#include "GraphManager.h"

namespace dgraph {

Region::Region():Node(), graph_manager_{std::make_shared<GraphManager>()} {
  SetNodeType(NodeType::REGION);
}

Region::~Region() {
  std::cout << "~Region()" << std::endl;
}

bool Region::RegisterNode (Node*& node,
                           std::set<Node*> const& dependency_nodes,
                           const std::string node_name) {
  std::cout << "Region register: " << node_name << std::endl;

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  graph_manager_->AddNode(node);
  return true;
}

bool Region::RegisterNode(
    Node*& node,
    std::set<Node*> const& dependency_nodes,
    const std::string node_name,
    int const& loop_count) {
  std::cout << "Region register: " << node_name << std::endl;

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  node->SetLoopCount(loop_count);
  graph_manager_->AddNode(node);
  return true;
}

void Region::Init() {
  graph_manager_->SetThreadPool(tp_);
  graph_manager_->Init();
}

void Region::run_before() {
  
}

void Region::run() {
  run_before();
  graph_manager_->Run();
  run_after();
}

void Region::run_after() {
  
}

} // namespace dgraph