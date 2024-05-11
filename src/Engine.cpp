#include "Engine.h"

#include <functional>

#include "Node.h"
#include "GraphManager.h"

Engine::Engine() : node_have_been_run_count_{0}, graph_manager_{nullptr} {}

void Engine::Init(std::shared_ptr<GraphManager>& graph_manager) {
  std::cout << "Engine Init\n";
  graph_manager_ = graph_manager;

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
  is_running_ = true;
  int total_node_count{graph_manager_->GetNodeCount()};
  std::cout << "\n\n************** Engine Run total node count: "
            << total_node_count << " ***************\n"
            << std::endl;

  // 可以一直按照DAG顺序运行
  thread_pool_ptr_->execute([this]() {
    while (is_running_) {
      for (auto node : graph_manager_->GetRunAbleNode()) {
        std::cout << "Add " << node->GetNodeName() << " to thread pool\n";
        thread_pool_ptr_->execute(std::bind(&Node::Process, node));
      }
    }
  });

}

void Engine::Deinit() {
  is_running_ = false;
}