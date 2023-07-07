#include "Node.h"
#include <iostream>
#include <thread>

class MyNode1 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode2 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode3 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode4 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode5 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class LoopNode : public Node {
  void run() override {
    while (true) {
      std::cout << Node::GetNodeName() << " running...\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << Node::GetNodeName() << " run over\n";
    }
  }
};