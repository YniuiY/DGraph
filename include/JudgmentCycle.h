#ifndef JUDGE_CYCLE_H_
#define JUDGE_CYCLE_H_

#include <set>
#include <map>
#include <memory>
#include <array>
#include <stack>

class Node;
class JudgmentCycle {
 public:
  JudgmentCycle();
  void Init(std::set<std::shared_ptr<Node>> const&);
  bool HasCycle();
  void CycleNodes();
  std::stack<std::shared_ptr<Node>> GetOrder();

 private:
  void dfs(std::shared_ptr<Node> const&);
  void check_cycle();
  bool is_cycle_;
  std::set<std::shared_ptr<Node>> marked_;
  std::set<std::shared_ptr<Node>> on_stack_;
  std::set<std::shared_ptr<Node>> adjs_;
  std::map<std::string, std::string> edge_to_;
  std::stack<std::string> cycle_node_;
  std::stack<std::shared_ptr<Node>> node_order_;
};

#endif