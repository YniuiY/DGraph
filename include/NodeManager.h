/**
 * 存储整个DAG的节点，后续可能需要这个类分析DAG是否有环。
 */

#ifndef NODE_MANAGER_H_
#define NODE_MANAGER_H_

#include <iostream>
#include <memory>
#include <set>
#include <vector>

class Node;
class NodeManager {
 public:
  void Init();

  std::vector<std::shared_ptr<Node>> GetRunAbleNode();

  int GetNodeCount();

  void AddNode(std::shared_ptr<Node>& node);

  void RemoveNode(std::shared_ptr<Node>& node);

 private:
  std::set<std::shared_ptr<Node>> node_set_;
};

#endif