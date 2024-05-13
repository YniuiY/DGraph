#include <iostream>
#include <functional>
#include "DGraph.h"
#include "Region/Region.h"
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

    std::shared_ptr<dgraph::Region> region = std::make_shared<dgraph::Region>();
    region->RegisterNode(b, {}, "NodeB");      // 注册节点b，命名为NodeB
    region->RegisterNode(c, {b}, "NodeC");     // 注册节点c，命名为NodeC，依赖节点b
    region->RegisterNode(d, {b}, "NodeD");     // 注册节点d，命名为NodeD，依赖节点b
    region->RegisterNode(e, {c, d}, "NodeE");     // 注册节点e，命名为NodeE，依赖节点b和c
    std::shared_ptr<Node> region_node = std::dynamic_pointer_cast<Node>(region);

    DGraph* graph = new DGraph();
    graph->RegisterNode(a, {}, "NodeA");      // 注册节点a，命名为NodeA
    graph->RegisterNode(region_node, {a}, "RegionNode", 2);     // 注册Region节点，命名为RegionNode，依赖节点a
    graph->RegisterNode(f, {region_node}, "NodeF");     // 注册节点f，命名为NodeF，依赖Region节点
   #endif

    graph->Init();
    graph->CheckCycle();
    graph->TopologicalSort();

    graph->Run();
    graph->Deinit();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}