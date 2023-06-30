/**
 * 存储整个DAG的节点，后续可能需要这个类分析DAG是否有环。
 */

#ifndef NODE_MANAGER_H_
#define NODE_MANAGER_H_

#include <iostream>
#include <vector>
#include <set>

class Node;
class NodeManager {
 public:

  void Init();

  std::vector<Node*> GetRunAbleNode();

  int GetNodeCount();

  void AddNode(Node*& node);

  void RemoveNode(Node*& node);

 private:
  std::set<Node*> node_set_;
};

#endif