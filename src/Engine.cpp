#include <functional>

#include "Engine.h"
#include "NodeManager.h"
#include "Node.h"

void Engine::Init(NodeManager * node_manager) {
  std::cout << "Engine Init\n";
  running_done_node_count_ = 0;
  node_manager_ = node_manager;

  int maxCount = 18;
  int coreCount = 8;
  int taskQueueLength = 8;
  Policy policy = Discard;
  int liveTime = 2;
  Unit unit = Second;
  thread_pool_ptr_ = new ThreadPool(maxCount, coreCount, taskQueueLength, policy, liveTime, unit);
}

void Engine::Run() {
  int total_node_count{node_manager_->GetNodeCount()};
  std::cout << "\n\n ************** Engine Run total node count: " << total_node_count << " ***************\n" << std::endl;

  while (running_done_node_count_ < total_node_count) {
    for (auto node : node_manager_->GetRunAbleNode()) {
      std::cout << "Add " << node->GetNodeName() << " to thread pool\n";
      thread_pool_ptr_->execute(std::bind(&Node::Process, node));
      running_done_node_count_++;
    }
  }
}

void Engine::Deinit() {
  if (thread_pool_ptr_ != nullptr) {
    delete thread_pool_ptr_;
    thread_pool_ptr_ = nullptr;
  }

}