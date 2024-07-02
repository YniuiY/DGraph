#include "Engine.h"

#include <functional>

#include "Node.h"
#include "GraphManager.h"

Engine::Engine() : is_running_(false),
                   thread_pool_ptr_(nullptr),
                   finished_node_num_{0},
                   is_region_{false},
                   runable_entry_node_num_{0} {

}

Engine::Engine(bool is_region) : is_running_(false),
                   thread_pool_ptr_(nullptr),
                   finished_node_num_{0},
                   is_region_{is_region},
                   runable_entry_node_num_{0} {
  
}

Engine::~Engine() {
  std::cout << "~Engine()\n";
}

void Engine::Init(std::set<Node*> const& node_set, std::shared_ptr<ThreadPool> const& thread_pool_ptr) {
  std::cout << "Engine Init\n";
  node_set_ = node_set;
  thread_pool_ptr_ = thread_pool_ptr;
  find_entry_node();
  std::cout << "Engine Init Done\n";
}

void Engine::Run() {
  std::cout << "Engine Running\n";
  is_running_ = true;

  if (alone_nodes_.size() > 0) {
    for (auto node : alone_nodes_) {
      thread_pool_ptr_->Commit(std::bind(&Engine::node_run, this, node));
    }
  }

  if (entry_nodes_.size() > 0) {
    // 可以一直按照DAG运行
    if (is_region_) {
      // 如果是Region的engine，将起始节点放入线程池中执行，阻塞等待最后一个节点执行完毕
      for (auto node : entry_nodes_) {
        thread_pool_ptr_->Commit(std::bind(&Engine::node_run, this, node));
      }
      std::unique_lock<std::mutex> lk(mtx_);
      cv_.wait(lk);
    } else {
      // 如果是普通的engine，直接按照DAG循环执行
      while (is_running_) {
        for (auto node : entry_nodes_) {
          if (node->IsRunable()) {
            --runable_entry_node_num_;
            std::cout << "--runable_entry_node_num_: " << runable_entry_node_num_ << std::endl;
            thread_pool_ptr_->Commit(std::bind(&Engine::node_run, this, node));
          }
        }

        // 如果入口节点执行快于后续DAG节点，不会进入阻塞，Engine一直运行
        // 如果入口节点执行慢于后续DAG节点，会进入阻塞，等待至少一个入口节点执行完成
        if (runable_entry_node_num_ <= 0) {
          std::unique_lock<std::mutex> lk(entry_mtx_);
          if (runable_entry_node_num_ <= 0) {
            std::cout << "runable_entry_node_num_ is: " << runable_entry_node_num_ << " waitting..." << std::endl;
            entry_cv_.wait(lk);
          }
        }
      }
    }
  }

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

void Engine::node_run(Node* const& node) {
  if (node == nullptr) {
    std::runtime_error("node is nullptr");
  }
  node->Process();
  node_run_after(node);
}

void Engine::node_run_after(Node* const& node) {
  for (auto node_after : node->GetRightNode()) {
    if (node_after->GetIndegreeDecrease() == 0) {
      std::cout << node->GetNodeName() << " right node: " << node_after->GetNodeName() << " indegree is 0\n";
      thread_pool_ptr_->Commit(std::bind(&Engine::node_run, this, node_after));
    }
  }

  // 如果节点是入口节点，通知阻塞的Run函数
  if (node->IsEntryNode()) {
    std::unique_lock<std::mutex> lk(entry_mtx_);
    runable_entry_node_num_++;
    std::cout << "runable_entry_node_num_: " << runable_entry_node_num_ << "\n";
    entry_cv_.notify_one();
  }

  if (is_region_ && ++finished_node_num_ >= node_set_.size() && node->GetRightNode().size() <= 0) {
    // 如果是Region的engine，执行完最后一个节点通知阻塞的Run函数
    // 没有后驱节点 且 node_set中全部节点都执行完毕
    // 通知GraphManager，结束阻塞
    cv_.notify_one();
  }
  // if (node->GetRightNode().size() <= 0) {
  //   std::cout << "\n\n************ Loop Once ************\n\n";
  // }
  // std::cout << "finished_node_num_: " << finished_node_num_ << " total node size: " << node_set_.size() << "\n";
}

void Engine::find_entry_node() {
  if (node_set_.size() == 1) {
    entry_nodes_.emplace_back(*node_set_.begin());
  }
  for (auto node : node_set_) {
    if (node->GetIndegree() == 0) {
      if (node->GetRightNode().size() > 0) {
        entry_nodes_.emplace_back(node);
        node->SetEntryNode(true);
        std::cout << "entry node: " << node->GetNodeName() << "\n";
      } else {
        alone_nodes_.emplace_back(node);
        std::cout << "alone node: " << node->GetNodeName() << "\n";
      }
    }
  }

  runable_entry_node_num_ = entry_nodes_.size();
  std::cout << "init runable_entry_node_num_: " << runable_entry_node_num_ << "\n";
}