/**
 * DAG中的节点基类，存储了他的依赖和依赖他的节点信息。
 * 实际运行的节点需要继承这个类，重新私有的run函数。
 */

#ifndef NODE_H_
#define NODE_H_

#include <atomic>
#include <iostream>
#include <memory>
#include <set>
#include <vector>

class Node {
 public:
  enum class NodeState {
    CREATED = 0,
    INITING,
    INITED,
    RUNNING_WAITING,
    RUNNING,
    RUNNING_DONE
  };

  enum class NodeType {
    TRIGGER = 0,
    LOOP = 1
  };

  Node();
  void Process();

  void RunBefore();

  void RunAfter();

  bool IsRunable();

  void AddDependencyNodes(std::set<std::shared_ptr<Node>> const&);

  void SetNodeName(std::string const& name);

  void SetNodeType(NodeType type);

  std::string GetNodeName();

  void SetNodeState(NodeState const& state);

  NodeState GetNodeState();

  std::set<std::shared_ptr<Node>> GetRightNode();

  std::set<std::shared_ptr<Node>> GetLeftNode();

  int& GetIndegree();

 private:
  virtual void run();

  /**
   * @brief 此节点的依赖的节点集合（邻接表），它的前置节点
   */
  std::set<std::shared_ptr<Node>> left_dependency_node_;
  /**
   * 依赖此节点的节点集合（邻接表），它的后驱节点
   */
  std::set<std::shared_ptr<Node>> right_be_dependency_node_;
  /**
   * @brief 前置依赖项数（入度），归零即可执行此节点
   */
  std::atomic<uint32_t> left_dep_count_;

  // 记录最初的入度，在运行结束后恢复入度，准备下一轮运行
  std::uint32_t static_left_dep_count_;

  /// @brief 入度（前置依赖项数）
  int indegree_;

  std::string node_name_;

  std::atomic<NodeState> node_state_;

  NodeType node_type_;
};

#endif