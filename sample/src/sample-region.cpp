#include <iostream>
#include <functional>
#include "DGraph.h"
#include "Region/Region.h"
#include "MyNode.h"

/**
 * @brief 测试Region节点
 * @details 测试Region节点，包括注册节点、设置Loop、依赖节点、运行节点等功能
 */

#define TEST_DIRECTED_GRAPH_1 1

int main() {
  try {
   #if TEST_DIRECTED_GRAPH_1
    Node* a = nullptr;
    Node* b = nullptr;
    Node* c = nullptr;
    Node* d = nullptr;
    Node* e = nullptr;
    Node* f = nullptr;

    dgraph::Region* region = new dgraph::Region();
    region->RegisterNode<MyNode1>(b, {}, "NodeB");      // 注册节点b，命名为NodeB
    region->RegisterNode<MyNode1>(c, {b}, "NodeC");     // 注册节点c，命名为NodeC，依赖节点b
    region->RegisterNode<MyNode1>(d, {b}, "NodeD");     // 注册节点d，命名为NodeD，依赖节点b
    region->RegisterNode<MyNode1>(e, {c, d}, "NodeE");  // 注册节点e，命名为NodeE，依赖节点b和c
    Node* region_node = dynamic_cast<Node*>(region); // 转换成基类Node类型的指针

    std::shared_ptr<DGraph> graph = std::make_shared<DGraph>();
    graph->RegisterNode<MyNode1>(a, {}, "NodeA");                        // 注册节点a，命名为NodeA
    graph->RegisterNode<dgraph::Region>(region_node, {a}, "LoopRegionNode", 2);  // 注册Region节点，命名为LoopRegionNode，依赖节点a
    graph->RegisterNode<MyNode1>(f, {region_node}, "NodeF");             // 注册节点f，命名为NodeF，依赖Region节点
   #endif

    graph->Init();
    graph->Run();
    graph->Deinit();

    return 0;
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}