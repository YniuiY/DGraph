#include <iostream>
#include <functional>
#include "DGraph.h"
#include "MyNode.h"

int main() {
  Node* a = new MyNode1();
  Node* b = new MyNode2();
  Node* c = new MyNode3();
  Node* d = new MyNode5();

  DGraph* graph = new DGraph();
  graph->Init();
  graph->RegisterNode(a, {}, "NodeA");      // 注册节点a,命名为NodeA
  graph->RegisterNode(b, {a}, "NodeB");     // 注册节点b,命名为NodeB，依赖节点a
  graph->RegisterNode(c, {a}, "NodeC");     // 注册节点c,命名为NodeC，依赖节点a
  graph->RegisterNode(d, {b, c}, "NodeD");  // 注册节点d,命名为NodeD，依赖节点b和c

  graph->Run();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  graph->Deinit();
}