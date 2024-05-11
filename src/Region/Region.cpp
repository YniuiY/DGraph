#include "Region/Region.h"

#include "GraphManager.h"

namespace dgraph {

Region::Region():Node(), graph_manager_{std::make_shared<GraphManager>()} {
  SetNodeType(NodeType::REGION);
}

Region::~Region() {

}

bool Region::RegisterNode (std::shared_ptr<Node>& node,
                           std::set<std::shared_ptr<Node>> const& dependency_nodes,
                           const std::string node_name) {
  std::cout << "Region register: " << node_name << std::endl;

  node->SetNodeName(node_name);
  node->AddDependencyNodes(dependency_nodes);
  graph_manager_->AddNode(node);
  return true;
}

bool Region::RegisterNode(
    std::shared_ptr<Node>& node,
    std::set<std::shared_ptr<Node>> const& dependency_nodes,
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