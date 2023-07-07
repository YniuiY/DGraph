#include <iostream>
#include <functional>
#include "DGraph.h"
#include "MyNode.h"

int main() {
  std::shared_ptr<Node> a = std::make_shared<MyNode1>();
  std::shared_ptr<Node> b = std::make_shared<MyNode5>();
  std::shared_ptr<Node> c = std::make_shared<MyNode3>();
  std::shared_ptr<Node> d = std::make_shared<MyNode1>();
  std::shared_ptr<Node> e = std::make_shared<MyNode1>();
  std::shared_ptr<Node> f = std::make_shared<MyNode1>();
  std::shared_ptr<Node> g = std::make_shared<MyNode1>();
  std::shared_ptr<Node> h = std::make_shared<LoopNode>();

  DGraph* graph = new DGraph();
  graph->Init();
  graph->RegisterNode(a, {}, "NodeA");      // 注册节点a，命名为NodeA
  graph->RegisterNode(b, {a}, "NodeB");     // 注册节点b，命名为NodeB，依赖节点a
  graph->RegisterNode(c, {a}, "NodeC");     // 注册节点c，命名为NodeC，依赖节点a
  graph->RegisterNode(d, {a}, "NodeD");     // 注册节点d，命名为NodeD，依赖节点a
  graph->RegisterNode(e, {b, c}, "NodeE");  // 注册节点e，命名为NodeE，依赖节点b和c
  graph->RegisterNode(f, {d, e}, "NodeF");  // 注册节点f，命名为NodeF，依赖节点d和e
  graph->RegisterNode(g, {}, "NodeG");      // 注册节点g，命名为NodeG
  graph->RegisterNode(h, {}, "LoopNode1"); // 注册一个loop节点h,

  // graph->RegisterNode(c, {f}, "NodeC");     // 注册节点c，命名为NodeC，依赖节点f。注意：此项会使graph成环, 图结构见image目录Directed_ring_graph.jpg

  graph->CheckCycle();

  graph->Run();
  std::this_thread::sleep_for(std::chrono::seconds(1));
  graph->Deinit();
}