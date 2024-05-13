#include "Engine.h"

#include <functional>

#include "Node.h"
#include "GraphManager.h"

Engine::Engine() : is_running_(false), thread_pool_ptr_(nullptr), finished_node_num_{0} {

}

Engine::~Engine() {
  std::cout << "~Engine()\n";
}

void Engine::Init(std::set<shared_ptr<Node>> const& node_set, std::shared_ptr<ThreadPool> const& thread_pool_ptr) {
  std::cout << "Engine Init\n";
  node_set_ = node_set;
  thread_pool_ptr_ = thread_pool_ptr;
  find_entry_node();
  std::cout << "Engine Init Done\n";
}

void Engine::Run() {
  std::cout << "Engine Running\n";
  is_running_ = true;

  // 可以一直按照DAG运行
  for (auto node : entry_nodes) {
    thread_pool_ptr_->execute(std::bind(&Engine::node_run, this, node));
  }

  /// TODO: 等待node_set中所有节点执行完毕
  std::unique_lock<std::mutex> lck(mtx_);
  cv_.wait(lck);
  finished_node_num_ = 0;
  std::cout << "Engine Running Done\n";
}

void Engine::Deinit() {
  is_running_ = false;
}

void Engine::run_before() {
  for (auto node : node_set_) {
    //
  }
}

void Engine::node_run(std::shared_ptr<Node> const& node) {
  node->Process();
  node_run_after(node);
}

void Engine::node_run_after(std::shared_ptr<Node> const& node) {
  for (auto node_after : node->GetRightNode()) {
    if (node_after->GetIndegree() <= 0) {
      std::cout << node->GetNodeName() << " right node: " << node_after->GetNodeName() << " indegree is 0\n";
      thread_pool_ptr_->execute(std::bind(&Engine::node_run, this, node_after));
    }
  }
  if (++finished_node_num_ >= node_set_.size() && node->GetRightNode().size() <= 0) {
    // 没有后驱节点 且 node_set中全部节点都执行完毕
    // 通知GraphManager，结束阻塞
    cv_.notify_one();
  }
  std::cout << "finished_node_num_: " << finished_node_num_ << " total node size: " << node_set_.size() << "\n";
}

void Engine::find_entry_node() {
  for (auto node : node_set_) {
    if (node->GetIndegree() == 0) {
      entry_nodes.emplace_back(node);
      std::cout << "entry node: " << node->GetNodeName() << "\n";
    }
  }
}