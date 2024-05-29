/**
 * 存储整个DAG的节点，分析DAG是否有环，管理维护拓扑。
 */

#ifndef GRAPH_MANAGER_H_
#define GRAPH_MANAGER_H_

#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <stack>

#include "Node.h"

class JudgmentCycle;
class TopologicalSort;
class Engine;
class ThreadPool;
class GraphManager {
 public:
  enum class EngineType {
    GRAPH_ENGINE,
    REGION_ENGINE
  };

  GraphManager();
  explicit GraphManager(EngineType const& engine_type);
  ~GraphManager();

  void Init();

  void Run();

  void Deinit();

  template<class NodeType>
  bool RegisterNode(Node*& node,
                    std::set<Node*> const& dependency_nodes,
                    std::string node_name,
                    int const& loop_count) {
    std::cout << "RegisterNode in GraphManager\n";
    if(node == nullptr) {
      node = new NodeType();
    }

    if (node != nullptr) {
      node->SetNodeName(node_name);
      node->SetLoopCount(loop_count);
      node->AddDependencyNodes(dependency_nodes);
      AddNode(node);
    } else {
      std::cout << "node is nullptr\n";
      return false;
    }
    return true;
  }

  void SetThreadPool(std::shared_ptr<ThreadPool> const& thread_pool); 

  int GetNodeCount();

  void AddNode(Node*& node);

  void RemoveNode(Node*& node);

  bool HasCycle();

  void TopoSort();

 private:
  /// @brief DAG所有节点的集合，因为每个节点都要自己的邻接点，所以这个set就是完整的邻接表
  std::set<Node*> node_set_;
  /// @brief DFS拓扑排序结果
  std::stack<Node*> order_node_stack_;
  /// @brief 拓扑排序结果
  std::vector<Node*> order_node_queue_;
  
  std::shared_ptr<JudgmentCycle> judgment_cycle_;
  std::shared_ptr<TopologicalSort> topo_sort_;

  std::shared_ptr<Engine> engine_;

  std::shared_ptr<ThreadPool> thread_pool_;
};

#endif