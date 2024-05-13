/**
 * 旧版：
 *      按照将DAG中的节点按照DAG的连接关系运行起来,
 *      循环检查执行完成的节点与总节点的数量，想等则执行完毕。
 *      每次循环将没有前置依赖的节点加入线程池执行。
 * 新版：
 *    1. 找出图的入口节点
 *    2. 将入口节点加入线程池执行
 *    3. 节点执行完毕后，对后驱节点进行依赖检查，如果依赖检查通过，则将后驱节点加入线程池执行
 *    4. 重复步骤3，直到所有节点执行完毕
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <memory>
#include <set>
#include <vector>

#include "threadpool/ThreadPool.hpp"

class Node;
class Engine {
 public:
  Engine();
  ~Engine();
  void Init(std::set<std::shared_ptr<Node>> const& node_set, std::shared_ptr<ThreadPool> const& thread_pool_ptr);

  /**
   * 从入口节点开始运行，在节点运行完成后，
   * 检查后驱节点，如果后驱节点没有前置依赖，则加入线程池执行
   * 直到所有节点执行完毕 
   */
  void Run();

  void Deinit();

 private:
  void find_entry_node();

  void node_run(std::shared_ptr<Node> const& node);

  /// @brief 节点运行前，设置状态
  void run_before();

  /// @brief 节点运行后，检查后驱节点，如果后驱节点前置依赖归零，则加入线程池执行
  void node_run_after(std::shared_ptr<Node> const& node);

  std::shared_ptr<ThreadPool> thread_pool_ptr_;   // 线程池
  std::vector<std::shared_ptr<Node>> entry_nodes; // 入口节点
  std::set<std::shared_ptr<Node>> node_set_;      // 全部节点集合
  bool is_running_;                               // 正在运行状态
  std::condition_variable cv_;                    // 阻塞Run函数的条件变量 
  std::mutex mtx_;                                // 
  int finished_node_num_;                         // 运行结束的节点数量
};

#endif