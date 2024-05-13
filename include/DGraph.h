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
  DGraph();
  ~DGraph();

  void Init();
  void Run();
  void Deinit();
  bool RegisterNode(Node*&,
                    std::set<Node*> const& dependency_nodes,
                    std::string node_name);

  bool RegisterNode(Node*&,
                    std::set<Node*> const& dependency_nodes,
                    std::string node_name,
                    int const& loop_count);

 private:
  void check_cycle();
  void topological_sort();

  std::shared_ptr<GraphManager> graph_manager_;
  std::shared_ptr<ThreadPool> thread_pool_;
};

#endif