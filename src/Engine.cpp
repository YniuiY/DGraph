#include "Engine.h"

#include <functional>

#include "Node.h"
#include "GraphManager.h"

Engine::Engine() : is_running_(false), thread_pool_ptr_(nullptr){}

void Engine::Init(std::set<shared_ptr<Node>> const& node_set, std::shared_ptr<ThreadPool> const& thread_pool_ptr) {
  std::cout << "Engine Init\n";
  node_set_ = node_set;
  thread_pool_ptr_ = thread_pool_ptr;
  find_entry_node();
}

void Engine::Run() {
  std::cout << "Engine Run\n";
  is_running_ = true;

  // 可以一直按照DAG运行
  for (auto node : entry_nodes) {
    thread_pool_ptr_->execute(std::bind(&Engine::node_run, this, node));
  }
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
      thread_pool_ptr_->execute(std::bind(&Engine::node_run, this, node_after));
    }
  }
}

void Engine::find_entry_node() {
  for (auto node : node_set_) {
    if (node->GetIndegree() == 0) {
      entry_nodes.emplace_back(node);
      std::cout << "entry node: " << node->GetNodeName() << "\n";
    }
  }
}