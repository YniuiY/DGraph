#include <iostream>
#include <functional>
#include "DGraph.h"
#include "MyNode.h"

#define TEST_DIRECTED_GRAPH_1 1
#define TEST_DIRECTED_GRAPH_2 0
#define TEST_DIRECTED_GRAPH_3 0

int main() {
  try {
   #if TEST_DIRECTED_GRAPH_1
    Node* a = nullptr;
    Node* b = nullptr;
    Node* c = nullptr;
    Node* d = nullptr;
    Node* e = nullptr;
    Node* f = nullptr;
    Node* g = nullptr;
    Node* h = nullptr;

    DGraph* graph = new DGraph();
    graph->RegisterNode<MyNode5>(a, {}, "NodeA");     // 注册节点a，命名为NodeA
    graph->RegisterNode<MyNode2>(b, {a}, "NodeB");     // 注册节点b，命名为NodeB，依赖节点a
    graph->RegisterNode<MyNode1>(c, {b}, "NodeC");     // 注册节点c，命名为NodeC，依赖节点a
    graph->RegisterNode<MyNode1>(d, {c}, "NodeD");     // 注册节点c，命名为NodeC，依赖节点a
    graph->RegisterNode<MyNode1>(e, {d}, "NodeE");     // 注册节点c，命名为NodeC，依赖节点a
    graph->RegisterNode<MyNode1>(f, {e}, "NodeF");     // 注册节点c，命名为NodeC，依赖节点a
    graph->RegisterNode<MyNode1>(g, {f}, "NodeG");     // 注册节点c，命名为NodeC，依赖节点a
    graph->RegisterNode<MyNode1>(h, {g}, "NodeH");     // 注册节点c，命名为NodeC，依赖节点a
   #endif

    graph->Init();
    graph->Run();
    graph->Deinit();

    return 0;
    std::cout << "Run Over\n";
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}