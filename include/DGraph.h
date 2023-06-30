/**
 * DGraph类，按照DAG注册上下游节点的依赖关系
 */

#ifndef DGRAPH_H_
#define DGRAPH_H_

#include <iostream>
#include <vector>
#include <set>
#include <functional>

#include "Node.h"
#include "NodeManager.h"
#include "Engine.h"

class DGraph {
 public:
  void Init();
  void Run();
  void Deinit();
  bool RegisterNode(Node*&, std::set<Node*>const& dependency_nodes, std::string node_name);

 private:
  NodeManager node_manager_;
  Engine engine_;
};

#endif