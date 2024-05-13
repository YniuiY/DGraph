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
    Node* a = new MyNode1();
    Node* b = new MyNode1();
    Node* c = new MyNode1();
    Node* d = new MyNode1();
    Node* e = new MyNode1();
    Node* f = new MyNode1();

    dgraph::Region* region = new dgraph::Region();
    region->RegisterNode(b, {}, "NodeB");      // 注册节点b，命名为NodeB
    region->RegisterNode(c, {b}, "NodeC");     // 注册节点c，命名为NodeC，依赖节点b
    region->RegisterNode(d, {b}, "NodeD");     // 注册节点d，命名为NodeD，依赖节点b
    region->RegisterNode(e, {c, d}, "NodeE");  // 注册节点e，命名为NodeE，依赖节点b和c
    Node* region_node = dynamic_cast<Node*>(region); // 转换成基类Node类型的指针

    std::shared_ptr<DGraph> graph = std::make_shared<DGraph>();
    graph->RegisterNode(a, {}, "NodeA");                        // 注册节点a，命名为NodeA
    graph->RegisterNode(region_node, {}, "LoopRegionNode", 2); // 注册Region节点，命名为LoopRegionNode，依赖节点a
    graph->RegisterNode(f, {region_node}, "NodeF");             // 注册节点f，命名为NodeF，依赖Region节点
   #endif

    graph->Init();
    graph->Run();
    graph->Deinit();
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}