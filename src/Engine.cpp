#include "Engine.h"

#include <functional>

#include "Node.h"
#include "NodeManager.h"

Engine::Engine() : node_have_been_run_count_{0} {}

void Engine::Init(std::shared_ptr<NodeManager>& node_manager) {
  std::cout << "Engine Init\n";
  node_manager_ = node_manager;

  int maxCount = 18;
  int coreCount = 8;
  int taskQueueLength = 8;
  Policy policy = Discard;
  int liveTime = 2;
  Unit unit = Second;

  std::cout << "\n**************************************************"
            << "\nInit thread pool:\nmax thread count: " << maxCount
            << "\ncore thread count: " << coreCount
            << "\ntask queu length: " << taskQueueLength
            << "\npolicy: " << policy
            << "\nempty thread live time: " << liveTime
            << "\nlive time unit: " << unit
            << "\n*************************************************\n"
            << std::endl;
  thread_pool_ptr_ = std::make_shared<ThreadPool>(
      maxCount, coreCount, taskQueueLength, policy, liveTime, unit);
}

void Engine::Run() {
  int total_node_count{node_manager_->GetNodeCount()};
  std::cout << "\n\n************** Engine Run total node count: "
            << total_node_count << " ***************\n"
            << std::endl;

  while (node_have_been_run_count_ < total_node_count) {
    for (auto node : node_manager_->GetRunAbleNode()) {
      std::cout << "Add " << node->GetNodeName() << " to thread pool\n";
      thread_pool_ptr_->execute(std::bind(&Node::Process, node));
      node_have_been_run_count_++;
    }
  }
}

void Engine::Deinit() {}