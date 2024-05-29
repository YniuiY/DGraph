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

    DGraph* graph = new DGraph();
    graph->RegisterNode<MyNode5>(a, {}, "NodeA");     // 注册节点a，命名为NodeA
    graph->RegisterNode<MyNode5>(b, {a}, "NodeB");     // 注册节点b，命名为NodeB，依赖节点a
    graph->RegisterNode<MyNode3>(c, {a}, "NodeC");     // 注册节点c，命名为NodeC，依赖节点a
    graph->RegisterNode<MyNode1>(d, {a}, "NodeD");     // 注册节点d，命名为NodeD，依赖节点a
    graph->RegisterNode<MyNode1>(e, {b, c}, "NodeE", 3);     // 注册节点e，命名为NodeE，依赖节点b和c
    graph->RegisterNode<MyNode1>(f, {d, e}, "NodeF");     // 注册节点f，命名为NodeF，依赖节点d和e
    graph->RegisterNode<MyNode1>(g, {}, "NodeG");     // 注册节点g，命名为NodeG
    // graph->RegisterNode<MyNode1>(c, {f}, "NodeC", 1);     // 注册节点c，命名为NodeC，依赖节点f。注意：此项会使graph成环, 图结构见image目录Directed_ring_graph.jpg
   #endif

   #if TEST_DIRECTED_GRAPH_2
    Node* a = nullptr;
    Node* b = nullptr;
    Node* c = nullptr;
    Node* d = nullptr;
    Node* e = nullptr;
    Node* f = nullptr;
    Node* g = nullptr;
    Node* h = nullptr;
    Node* i = nullptr;
    Node* j = nullptr;
    Node* k = nullptr;
    Node* l = nullptr;


    DGraph* graph = new DGraph();
    graph->RegisterNode<MyNode1>(a, {}, "NodeA");      // 注册节点a，命名为NodeA
    graph->RegisterNode<MyNode5>(b, {}, "NodeB");      // 注册节点b，命名为NodeB，依赖节点a
    graph->RegisterNode<MyNode1>(c, {a, b}, "NodeC");  // 注册节点c，命名为NodeC，依赖节点a,b
    graph->RegisterNode<MyNode5>(d, {a, c}, "NodeD");  // 注册节点d，命名为NodeD，依赖节点a,c
    graph->RegisterNode<MyNode5>(e, {d}, "NodeE");     // 注册节点e，命名为NodeE，依赖节点d
    graph->RegisterNode<MyNode1>(g, {c}, "NodeG");     // 注册节点g，命名为NodeG，依赖节点c
    graph->RegisterNode<MyNode1>(h, {d,g}, "NodeH");   // 注册节点h，命名为NodeH，依赖节点d,g
    graph->RegisterNode<MyNode5>(f, {e,h}, "NodeF");   // 注册节点f，命名为NodeF，依赖节点e,h
    graph->RegisterNode<MyNode1>(i, {h}, "NodeI");     // 注册节点i，命名为NodeI，依赖节点h
    graph->RegisterNode<MyNode1>(j, {f,i}, "NodeJ");   // 注册节点j，命名为NodeJ，依赖节点f,i
    graph->RegisterNode<MyNode5>(k, {j}, "NodeK");     // 注册节点k，命名为NodeK，依赖节点j
    graph->RegisterNode<MyNode1>(l, {j}, "NodeL");     // 注册节点l，命名为NodeL，依赖节点j
   #endif

   #if TEST_DIRECTED_GRAPH_3
    Node* a = nullptr;
    Node* b = nullptr;
    Node* c = nullptr;
    Node* d = nullptr;
    Node* e = nullptr;
    Node* f = nullptr;
    Node* g = nullptr;
    Node* h = nullptr;
    Node* i = nullptr;
    Node* j = nullptr;
    Node* k = nullptr;

    DGraph* graph = new DGraph();
    graph->RegisterNode<MyNode10>(a, {}, "GetImage");     // 注册节点a，命名为GetImage
    graph->RegisterNode<MyNode3>(b, {a}, "Clip");        // 注册节点b，命名为Clip，依赖节点a
    graph->RegisterNode<MyNode3>(c, {b}, "Cyl");         // 注册节点c，命名为Cyl，依赖节点b
    graph->RegisterNode<MyNode2>(d, {c}, "Pym");         // 注册节点d，命名为Pym，依赖节点c
    graph->RegisterNode<MyNode3>(e, {b}, "Ipm");         // 注册节点e，命名为Ipm，依赖节点b
    graph->RegisterNode<MyNode5>(f, {e}, "Stitch");      // 注册节点f，命名为Stitch，依赖节点e
    graph->RegisterNode<MyNode5>(g, {b}, "Desensitize"); // 注册节点g，命名为Desensitize，依赖节点b
    graph->RegisterNode<MyNode5>(h, {g}, "H265");        // 注册节点h，命名为H265，依赖节点g
    graph->RegisterNode<MyNode1>(i, {d}, "PubCyl");      // 注册节点i，命名为Pub，无依赖节点
    graph->RegisterNode<MyNode1>(j, {f}, "PubStitch");   // 注册节点i，命名为Pub，无依赖节点
    graph->RegisterNode<MyNode1>(k, {h}, "PubH265");     // 注册节点i，命名为Pub，无依赖节点
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