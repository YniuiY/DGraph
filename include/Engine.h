/**
 * 按照将DAG中的节点按照DAG的连接关系运行起来,
 * 循环检查执行完成的节点与总节点的数量，想等则执行完毕。
 * 每次循环将没有前置依赖的节点加入线程池执行。
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "threadpool/ThreadPool.hpp"
#include "NodeManager.h"

class Engine {
 public:
  void Init(NodeManager *);

  /**
   * @brief 运行整个DAG，每次遍历都取出没有前置依赖的节点，加入线程池运行，直到所以节点都运行完成
   */
  void Run();

  void Deinit();

 private:
  ThreadPool* thread_pool_ptr_;
  NodeManager* node_manager_;
  int running_done_node_count_;
};

#endif