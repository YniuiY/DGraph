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
    std::shared_ptr<Node> a = std::make_shared<MyNode5>();
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
    // graph->RegisterNode(g, {}, "NodeG");      // 注册节点g，命名为NodeG
    // graph->RegisterNode(h, {}, "LoopNode1"); // 注册一个loop节点h,
    // graph->RegisterNode(c, {f}, "NodeC");     // 注册节点c，命名为NodeC，依赖节点f。注意：此项会使graph成环, 图结构见image目录Directed_ring_graph.jpg
   #endif

   #if TEST_DIRECTED_GRAPH_2
    std::shared_ptr<Node> a = std::make_shared<MyNode1>();
    std::shared_ptr<Node> b = std::make_shared<MyNode5>();
    std::shared_ptr<Node> c = std::make_shared<MyNode1>();
    std::shared_ptr<Node> d = std::make_shared<MyNode5>();
    std::shared_ptr<Node> e = std::make_shared<MyNode5>();
    std::shared_ptr<Node> f = std::make_shared<MyNode5>();
    std::shared_ptr<Node> g = std::make_shared<MyNode1>();
    std::shared_ptr<Node> h = std::make_shared<MyNode1>();
    std::shared_ptr<Node> i = std::make_shared<MyNode1>();
    std::shared_ptr<Node> j = std::make_shared<MyNode1>();
    std::shared_ptr<Node> k = std::make_shared<MyNode5>();
    std::shared_ptr<Node> l = std::make_shared<MyNode1>();


    DGraph* graph = new DGraph();
    graph->Init();
    graph->RegisterNode(a, {}, "NodeA");      // 注册节点a，命名为NodeA
    graph->RegisterNode(b, {}, "NodeB");      // 注册节点b，命名为NodeB，依赖节点a
    graph->RegisterNode(c, {a, b}, "NodeC");  // 注册节点c，命名为NodeC，依赖节点a,b
    graph->RegisterNode(d, {a, c}, "NodeD");  // 注册节点d，命名为NodeD，依赖节点a,c
    graph->RegisterNode(e, {d}, "NodeE");     // 注册节点e，命名为NodeE，依赖节点d
    graph->RegisterNode(f, {e,h}, "NodeF");   // 注册节点f，命名为NodeF，依赖节点e,h
    graph->RegisterNode(g, {c}, "NodeG");     // 注册节点g，命名为NodeG，依赖节点c
    graph->RegisterNode(h, {d,g}, "NodeH");   // 注册节点h，命名为NodeH，依赖节点d,g
    graph->RegisterNode(i, {h}, "NodeI");     // 注册节点i，命名为NodeI，依赖节点h
    graph->RegisterNode(j, {f,i}, "NodeJ");   // 注册节点j，命名为NodeJ，依赖节点f,i
    graph->RegisterNode(k, {j}, "NodeK");     // 注册节点k，命名为NodeK，依赖节点j
    graph->RegisterNode(l, {j}, "NodeL");     // 注册节点l，命名为NodeL，依赖节点j
   #endif

   #if TEST_DIRECTED_GRAPH_3
    std::shared_ptr<Node> a = std::make_shared<MyNode10>();
    std::shared_ptr<Node> b = std::make_shared<MyNode3>();
    std::shared_ptr<Node> c = std::make_shared<MyNode3>();
    std::shared_ptr<Node> d = std::make_shared<MyNode2>();
    std::shared_ptr<Node> e = std::make_shared<MyNode3>();
    std::shared_ptr<Node> f = std::make_shared<MyNode5>();
    std::shared_ptr<Node> g = std::make_shared<MyNode5>();
    std::shared_ptr<Node> h = std::make_shared<MyNode5>();
    std::shared_ptr<Node> i = std::make_shared<MyNode1>();
    std::shared_ptr<Node> j = std::make_shared<MyNode1>();
    std::shared_ptr<Node> k = std::make_shared<MyNode1>();



    DGraph* graph = new DGraph();
    graph->Init();
    graph->RegisterNode(a, {}, "GetImage");     // 注册节点a，命名为GetImage
    graph->RegisterNode(b, {a}, "Clip");        // 注册节点b，命名为Clip，依赖节点a
    graph->RegisterNode(c, {b}, "Cyl");         // 注册节点c，命名为Cyl，依赖节点b
    graph->RegisterNode(d, {c}, "Pym");         // 注册节点d，命名为Pym，依赖节点c
    graph->RegisterNode(e, {b}, "Ipm");         // 注册节点e，命名为Ipm，依赖节点b
    graph->RegisterNode(f, {e}, "Stitch");      // 注册节点f，命名为Stitch，依赖节点e
    graph->RegisterNode(g, {b}, "Desensitize"); // 注册节点g，命名为Desensitize，依赖节点b
    graph->RegisterNode(h, {g}, "H265");        // 注册节点h，命名为H265，依赖节点g
    graph->RegisterNode(i, {d}, "PubCyl");      // 注册节点i，命名为Pub，无依赖节点
    graph->RegisterNode(j, {f}, "PubStitch");   // 注册节点i，命名为Pub，无依赖节点
    graph->RegisterNode(k, {h}, "PubH265");     // 注册节点i，命名为Pub，无依赖节点
   #endif


    graph->CheckCycle();
    graph->TopologicalSort();

    graph->Run();
    std::this_thread::sleep_for(std::chrono::seconds(30));
    graph->Deinit();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}