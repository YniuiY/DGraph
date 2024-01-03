#ifndef TOPOLOGICAL_H_
#define TOPOLOGICAL_H_

#include <set>
#include <queue>
#include <stack>
#include <iostream>

#include "Node.h"

class TopologicalSort {
 public:
  TopologicalSort(std::set<std::shared_ptr<Node>> adjs);
  std::queue<std::shared_ptr<Node>> Sort();
  std::stack<std::shared_ptr<Node>> DfsSort();
  void PrintOrder();

 private:
  void dfs(std::shared_ptr<Node> node);

  std::set<std::shared_ptr<Node>> adjs_;
  std::queue<std::shared_ptr<Node>> topological_order_;
  std::stack<std::shared_ptr<Node>> reverse_post_order_;
  std::set<std::shared_ptr<Node>> marked_;

  std::set<std::shared_ptr<Node>> on_stack_;
  bool has_cycle_;
};

#endif // TOPOLOGICAL_H_