/**
 * DGraph类，按照DAG注册上下游节点的依赖关系
 */

#ifndef DGRAPH_H_
#define DGRAPH_H_

#include <functional>
#include <iostream>
#include <set>
#include <vector>
#include <memory>

class Engine;
class Node;
class GraphManager;
class ThreadPool;
class DGraph {
 public:
  void Init();
  void CheckCycle();
  void Run();
  void Deinit();
  bool RegisterNode(std::shared_ptr<Node>&,
                    std::set<std::shared_ptr<Node>> const& dependency_nodes,
                    std::string node_name);

  bool RegisterNode(std::shared_ptr<Node>&,
                    std::set<std::shared_ptr<Node>> const& dependency_nodes,
                    std::string node_name,
                    int const& loop_count);
  void TopologicalSort();

 private:
  std::shared_ptr<GraphManager> graph_manager_;
  std::shared_ptr<ThreadPool> thread_pool_;
};

#endif