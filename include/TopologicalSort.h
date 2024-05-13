#ifndef TOPOLOGICAL_H_
#define TOPOLOGICAL_H_

#include <set>
#include <queue>
#include <stack>
#include <iostream>

#include "Node.h"

class TopologicalSort {
 public:
  TopologicalSort(std::set<Node*> adjs);
  ~TopologicalSort();
  std::vector<Node*> Sort();
  std::stack<Node*> DfsSort();
  void PrintOrder();

 private:
  void dfs(Node* node);

  std::set<Node*> adjs_;
  std::vector<Node*> topological_order_;
  std::stack<Node*> reverse_post_order_;
  std::set<Node*> marked_;

  std::set<Node*> on_stack_;
  bool has_cycle_;
};

#endif // TOPOLOGICAL_H_