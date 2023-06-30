/**
 * 按照将DAG中的节点按照DAG的连接关系运行起来,
 * 循环检查执行完成的节点与总节点的数量，想等则执行完毕。
 * 每次循环将没有前置依赖的节点加入线程池执行。
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <memory>

#include "threadpool/ThreadPool.hpp"
#include "NodeManager.h"

class Engine {
 public:
  Engine();
  void Init(std::shared_ptr<NodeManager>&);

  /**
   * @brief 运行整个DAG，每次遍历都取出没有前置依赖的节点，加入线程池运行，直到所以节点都运行完成
   */
  void Run();

  void Deinit();

 private:
  std::shared_ptr<ThreadPool> thread_pool_ptr_;
  std::shared_ptr<NodeManager> node_manager_;
  int node_have_been_run_count_;
};

#endif