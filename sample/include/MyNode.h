#include <iostream>
#include <thread>

#include "Node.h"
#include "ParamManager/Param.h"
#include "ParamManager/ParamManager.h"
#include "Utils/TimeUtil.h"

class MyNode1 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    if (GetLeftNode().size() > 0) {
      for (auto left_node: GetLeftNode()) {
        dgraph::Param const* param = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(left_node->GetNodeName());
        std::string const& topic = param->GetTopic();
        uint64_t timestamp = param->GetTimestamp();
        std::cout << Node::GetNodeName() << " get topic: " << topic << " data, data_timestamp: " << timestamp << "\n";
      }
    }
    std::shared_ptr<dgraph::Param> out_param{std::make_shared<dgraph::Param>()};
    out_param->Clear();
    out_param->SetTopic(GetNodeName());
    out_param->SetTimestamp(dgraph::TimeUtil::TimeNow());
    dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(GetNodeName(), out_param);
    std::cout << Node::GetNodeName() << " output topic: " << GetNodeName() << " param\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode2 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";

    if (GetLeftNode().size() > 0) {
      for (auto left_node: GetLeftNode()) {
        dgraph::Param const* param = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(left_node->GetNodeName());
        std::string const& topic = param->GetTopic();
        uint64_t timestamp = param->GetTimestamp();
        std::cout << Node::GetNodeName() << " get topic: " << topic << " data, data_timestamp: " << timestamp << "\n";
      }
    }
    std::shared_ptr<dgraph::Param> out_param{std::make_shared<dgraph::Param>()};
    out_param->Clear();
    out_param->SetTopic(GetNodeName());
    out_param->SetTimestamp(dgraph::TimeUtil::TimeNow());
    dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(GetNodeName(), out_param);
    std::cout << Node::GetNodeName() << " output topic: " << GetNodeName() << " param\n";

    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode3 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    
    if (GetLeftNode().size() > 0) {
      for (auto left_node: GetLeftNode()) {
        dgraph::Param const* param = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(left_node->GetNodeName());
        std::string const& topic = param->GetTopic();
        uint64_t timestamp = param->GetTimestamp();
        std::cout << Node::GetNodeName() << " get topic: " << topic << " data, data_timestamp: " << timestamp << "\n";
      }
    }
    std::shared_ptr<dgraph::Param> out_param{std::make_shared<dgraph::Param>()};
    out_param->Clear();
    out_param->SetTopic(GetNodeName());
    out_param->SetTimestamp(dgraph::TimeUtil::TimeNow());
    dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(GetNodeName(), out_param);
    std::cout << Node::GetNodeName() << " output topic: " << GetNodeName() << " param\n";

    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode4 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";

    if (GetLeftNode().size() > 0) {
      for (auto left_node: GetLeftNode()) {
        dgraph::Param const* param = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(left_node->GetNodeName());
        std::string const& topic = param->GetTopic();
        uint64_t timestamp = param->GetTimestamp();
        std::cout << Node::GetNodeName() << " get topic: " << topic << " data, data_timestamp: " << timestamp << "\n";
      }
    }
    std::shared_ptr<dgraph::Param> out_param{std::make_shared<dgraph::Param>()};
    out_param->Clear();
    out_param->SetTopic(GetNodeName());
    out_param->SetTimestamp(dgraph::TimeUtil::TimeNow());
    dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(GetNodeName(), out_param);
    std::cout << Node::GetNodeName() << " output topic: " << GetNodeName() << " param\n";

    std::this_thread::sleep_for(std::chrono::seconds(4));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode5 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    
    if (GetLeftNode().size() > 0) {
      for (auto left_node: GetLeftNode()) {
        dgraph::Param const* param = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(left_node->GetNodeName());
        std::string const& topic = param->GetTopic();
        uint64_t timestamp = param->GetTimestamp();
        std::cout << Node::GetNodeName() << " get topic: " << topic << " data, data_timestamp: " << timestamp << "\n";
      }
    }
    std::shared_ptr<dgraph::Param> out_param{std::make_shared<dgraph::Param>()};
    out_param->Clear();
    out_param->SetTopic(GetNodeName());
    out_param->SetTimestamp(dgraph::TimeUtil::TimeNow());
    dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(GetNodeName(), out_param);
    std::cout << Node::GetNodeName() << " output topic: " << GetNodeName() << " param\n";

    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class MyNode10 : public Node {
  void run() override {
    std::cout << Node::GetNodeName() << " running\n";
    std::this_thread::sleep_for(std::chrono::seconds(10));
    std::cout << Node::GetNodeName() << " running over\n";
  }
};

class LoopNode : public Node {
  void run() override {
    while (true) {
      RunBefore();
      std::cout << Node::GetNodeName() << " running...\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(10000));
      std::cout << Node::GetNodeName() << " run over\n";
      RunAfter();
    }
  }
};