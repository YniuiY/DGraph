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

class JudgmentCycle;
class TopologicalSort;
class Engine;
class ThreadPool;
class Node;

class GraphManager {
 public:
  GraphManager();
  ~GraphManager();

  void Init();

  void Run();

  void Deinit();

  void SetThreadPool(std::shared_ptr<ThreadPool> const& thread_pool); 

  int GetNodeCount();

  void AddNode(std::shared_ptr<Node>& node);

  void RemoveNode(std::shared_ptr<Node>& node);

  bool HasCycle();

  void TopoSort();

 private:
  /// @brief DAG所有节点的集合，因为每个节点都要自己的邻接点，所以这个set就是完整的邻接表
  std::set<std::shared_ptr<Node>> node_set_;
  /// @brief DFS拓扑排序结果
  std::stack<std::shared_ptr<Node>> order_node_stack_;
  /// @brief 拓扑排序结果
  std::vector<std::shared_ptr<Node>> order_node_queue_;
  
  std::shared_ptr<JudgmentCycle> judgment_cycle_;
  std::shared_ptr<TopologicalSort> topo_sort_;

  std::shared_ptr<Engine> engine_;

  std::shared_ptr<ThreadPool> thread_pool_;
};

#endif