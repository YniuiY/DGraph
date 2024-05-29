#include "Region/Region.h"

#include "GraphManager.h"
#include "ParamManager/ParamManager.h"
#include "Utils/TimeUtil.h"

namespace dgraph {

Region::Region():Node(), graph_manager_{std::make_shared<GraphManager>(GraphManager::EngineType::REGION_ENGINE)} {
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
  // TODO: 从前置节点获取他们的输出参数
  // for (auto left_node: GetLeftNode()) {
  //   Param const* param = ParamManager::GetInstance().GetParam<Param>(left_node->GetNodeName());
  //   if (param != nullptr)
  //     std::cout << GetNodeName() << " get param: " << param->GetTopic() << " frame id: " << param->GetFrameId() << std::endl;
  // }
}

void Region::run() {
  run_before();
  graph_manager_->Run();
  run_after();
}

void Region::run_after() {
  // TODO: 输出参数到后驱节点
  // std::shared_ptr<dgraph::Param> out_param{std::make_shared<dgraph::Param>()};
  // out_param->Clear();
  // out_param->SetTopic(GetNodeName());
  // out_param->SetTimestamp(TimeUtil::TimeNow());
  // dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(GetNodeName(), out_param);
  // std::cout << Node::GetNodeName() << " output topic: " << GetNodeName() << " param\n";
}

} // namespace dgraph