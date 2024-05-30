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
#include <mutex>

class ThreadPool;
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
    COMMON = 0,
    REGION = 1
  };

  Node();
  virtual ~Node();

  virtual void Init();

  void Process();

  void RunBefore();

  void RunAfter();

  bool IsRunable();

  void AddDependencyNodes(std::set<Node*> const&);

  void SetNodeName(std::string const& name);

  void SetNodeType(NodeType type);

  NodeType GetNodeType();

  std::string GetNodeName();

  void SetNodeState(NodeState const& state);

  NodeState GetNodeState();

  std::set<Node*> GetRightNode();

  std::set<Node*> GetLeftNode();

  int GetIndegree();

  int GetIndegreeDecrease(); // 获取入度减一后的值

  void IndegreeDecrease(); // 入度减一

  int& GetLeftDepCount();

  void SetLoopCount(int const& loop_count);

  int GetLoopCount();

  void SetThreadPool(std::shared_ptr<ThreadPool> const& tp);

 private:
  virtual void run();

  void indegree_reset(); // 恢复原始入度

  /**
   * @brief 此节点的依赖的节点集合（邻接表），它的前置节点
   */
  std::set<Node*> left_dependency_node_;
  /**
   * @brief 依赖此节点的节点集合（邻接表），它的后驱节点
   */
  std::set<Node*> right_be_dependency_node_;
  /**
   * @brief 前置依赖项数（入度）， 拓扑排序用
   */
  int left_dep_count_;

  /// @brief 记录最初的入度，在运行结束后恢复入度，准备下一轮运行
  std::uint32_t static_left_dep_count_;

  /// @brief 入度（前置依赖项数）
  int indegree_;

  /// @brief 多线程操作入度需要上锁
  std::mutex indegree_mutex_;

  /// @brief 节点名称
  std::string node_name_;

  /// @brief 节点状态
  std::atomic<NodeState> node_state_;

  /// @brief 节点类型
  NodeType node_type_;

  /// @brief 循环次数
  int loop_count_;

 protected:
  std::shared_ptr<ThreadPool> tp_;
};

using NodePtr = Node*;

#endif