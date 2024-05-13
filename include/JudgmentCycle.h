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
  ~JudgmentCycle();
  void Init(std::set<Node*> const&);
  bool HasCycle();
  void CycleNodes();
  std::stack<Node*> GetOrderNodeStack();
  void GetBfsFrontOrder();

 private:
  void dfs(Node* const&);
  void bfs(Node* const&);
  void check_cycle();
  bool is_cycle_;
  std::set<Node*> marked_;
  std::set<Node*> on_stack_;
  std::set<Node*> adjs_;
  std::map<std::string, std::string> edge_to_;
  std::stack<std::string> cycle_node_;
  std::stack<Node*> node_order_;
};

#endif