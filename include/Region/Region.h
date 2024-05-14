#ifndef DGRAPH_REGION_H_
#define DGRAPH_REGION_H_

#include <string>
#include <vector>

#include "GraphManager.h"
#include "Node.h"

namespace dgraph {

class Region : public Node {
 public:
  Region();
  ~Region();

  void Init() override; 

  bool RegisterNode(Node*& node,
                    std::set<Node*> const& dependency_nodes,
                    const std::string node_name);
  
  bool RegisterNode(Node*& node,
                    std::set<Node*> const& dependency_nodes,
                    const std::string node_name,
                    int const& loop_count);

  template <class NodeType>
  bool RegisterNode(Node*& node,
                    std::set<Node*> const& dependency_nodes,
                    const std::string node_name,
                    int const& loop_count) {
    return graph_manager_->RegisterNode<NodeType>(node, dependency_nodes, node_name, loop_count);
  }
 private:
  void run() override;
  void run_before();
  void run_after();

  std::shared_ptr<GraphManager> graph_manager_;
};

} // namespace dgraph

#endif // DGRAPH_REGION_H_