#ifndef NODE_H_
#define NODE_H_

#include <iostream>
#include <vector>
#include <set>
#include <atomic>

class Node {
 public:
  Node();
  void Process();

  void RunBefore();

  void RunAfter();

  bool IsRunable();

  void AddDependencyNodes(std::set<Node*>const&);

  void SetNodeName(std::string const& name);

  std::string GetNodeName();
 private:
  virtual void run();
  /**
   * @brief 此节点的依赖的节点集合，它的前置节点
   */
  std::set<Node*> left_dependency_node_;
  /**
   * 依赖此节点的节点集合，它的后驱节点
   */     
  std::set<Node*> right_be_dependency_node_;
  /**
   * @brief 前置依赖项数，归零即可执行此节点
   */
  std::atomic<uint32_t> left_dep_count_;

  std::string node_name_;

  std::atomic<bool> running_done_;

  std::atomic<bool> running_;
};

#endif