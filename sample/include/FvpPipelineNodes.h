#ifndef FVP_PIPELINES_NODES_H_
#define FVP_PIPELINES_NODES_H_

#include "Node.h"
#include "Utils/TimeUtil.h"
#include <thread>

class Vio : public Node {
  void run() override {
    std::cout << "Vio running\n";
    while (dgraph::TimeUtil::TimeNow() - timestamp_ < time_interval_) {
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }
    timestamp_ = dgraph::TimeUtil::TimeNow();
    std::cout << "Vio run over" << std::endl;
  }

  int64_t timestamp_;
  int64_t time_interval_ = 33000; // 3300ms
};

class Gdc : public Node {
  void run() override {
    std::cout << "Gdc running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    std::cout << "Gdc run over" << std::endl;
  }
};

class GdcFree : public Node {
  void run() override {
    std::cout << "Gdc free running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::cout << "Gdc free run over" << std::endl;
  }
};

class Pym : public Node {
  void run() override {
    std::cout << "Pym running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    std::cout << "Pym run over" << std::endl;
  }
};

class PymFree : public Node {
  void run() override {
    std::cout << "Pym free running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::cout << "Pym free run over" << std::endl;
  }
};

class H265Input : public Node {
  void run() override {
    std::cout << "H265Input running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    std::cout << "H265Input run over" << std::endl;
  }
};

class H265Output : public Node {
  void run() override {
    std::cout << "H265Output running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    std::cout << "H265Output run over" << std::endl;
    std::cout << "Callback H265\n";
  }
};

class Roi0 : public Node {
  void run() override {
    std::cout << "ROI0 running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::cout << "ROI0 run over" << std::endl;
    std::cout << "Callback Roi0\n";
  }
};

class Roi1 : public Node {
  void run() override {
    std::cout << "ROI1 running\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::cout << "ROI1 run over" << std::endl;
    std::cout << "Callback Roi1\n";
  }
};

class Roi2 : public Node {
  void run() override {
    std::cout << "ROI2 running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::cout << "ROI2 run over" << std::endl;
    std::cout << "Callback Roi2\n";
  }
};

class Roi3 : public Node {
  void run() override {
    std::cout << "ROI3 running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::cout << "ROI3 run over" << std::endl;
    std::cout << "Callback Roi3\n";
  }
};

class Sink : public Node {
  void run() override {
    std::cout << "Sink running" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    std::cout << "Sink run over" << std::endl;
  }
};

#endif // FVP_PIPELINES_NODES_H_