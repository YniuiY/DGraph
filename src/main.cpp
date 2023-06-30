#include <iostream>
#include <functional>
#include "DGraph.h"
#include "MyNode.h"

int main() {
  Node* a = new MyNode1();
  Node* b = new MyNode1();
  Node* c = new MyNode3();
  Node* d = new MyNode1();
  Node* e = new MyNode1();
  Node* f = new MyNode5();

  DGraph* graph = new DGraph();
  graph->Init();
  graph->RegisterNode(a, {}, "NodeA");      // 注册节点a,命名为NodeA
  graph->RegisterNode(b, {a}, "NodeB");     // 注册节点b,命名为NodeB，依赖节点a
  graph->RegisterNode(c, {a}, "NodeC");     // 注册节点c,命名为NodeC，依赖节点a
  graph->RegisterNode(d, {a}, "NodeD");     // 注册节点d,命名为NodeD，依赖节点a
  graph->RegisterNode(e, {b, c}, "NodeE");  // 注册节点e,命名为NodeE，依赖节点b和c
  graph->RegisterNode(f, {d, e}, "NodeF");  // 注册节点f,命名为NodeF，依赖节点d和e

  graph->Run();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  graph->Deinit();
}