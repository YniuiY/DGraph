/**
 * DGraph类，按照DAG注册上下游节点的依赖关系
 */

#ifndef DGRAPH_H_
#define DGRAPH_H_

#include <functional>
#include <iostream>
#include <set>
#include <vector>

#include "Engine.h"
#include "Node.h"
#include "NodeManager.h"

class DGraph {
 public:
  void Init();
  void CheckCycle();
  void Run();
  void Deinit();
  bool RegisterNode(std::shared_ptr<Node>&,
                    std::set<std::shared_ptr<Node>> const& dependency_nodes,
                    std::string node_name);

 private:
  std::shared_ptr<NodeManager> node_manager_;
  Engine engine_;
};

#endif