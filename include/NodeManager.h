/**
 * 存储整个DAG的节点，后续可能需要这个类分析DAG是否有环。
 */

#ifndef NODE_MANAGER_H_
#define NODE_MANAGER_H_

#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <stack>

#include "JudgmentCycle.h"
#include "TopologicalSort.h"

class Node;
class NodeManager {
 public:
  NodeManager();
  ~NodeManager();

  void Init();

  std::vector<std::shared_ptr<Node>> GetRunAbleNode();

  int GetNodeCount();

  void AddNode(std::shared_ptr<Node>& node);

  void RemoveNode(std::shared_ptr<Node>& node);

  bool HasCycle();

  void TopoSort();

 private:
  /// @brief DAG所有节点的集合
  std::set<std::shared_ptr<Node>> node_set_;
  /// @brief DFS拓扑排序结果
  std::stack<std::shared_ptr<Node>> order_node_stack_;
  /// @brief 拓扑排序结果
  std::queue<std::shared_ptr<Node>> order_node_queue_;
  
  JudgmentCycle judgment_cycle_;
  std::shared_ptr<TopologicalSort> topo_sort_;
};

#endif