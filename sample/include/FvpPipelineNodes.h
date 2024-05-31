#ifndef FVP_PIPELINES_NODES_H_
#define FVP_PIPELINES_NODES_H_

#include "Node.h"
#include "ParamManager/ParamManager.h"
#include "Utils/TimeUtil.h"
#include <thread>

static const std::string VioTopic{"VioOutput"};
static const std::string GdcTopic{"GdcOutput"};
static const std::string PymTopic{"PymOutput"};


class Vio : public Node {
  void run() override {
    std::cout << "Vio running\n";
    while (dgraph::TimeUtil::TimeNow() - timestamp_ < time_interval_) {
      std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    timestamp_ = dgraph::TimeUtil::TimeNow();
    dgraph::Param vio_data;
    raw_image_ = new std::uint8_t[raw_image_size_];
    vio_data.SetData(raw_image_, raw_image_size_);
    vio_data.SetTimestamp(timestamp_);
    vio_data.SetTopic(VioTopic);
    dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(VioTopic, vio_data);
    std::cout << "Vio output image, ptr: " << std::hex << (std::uint64_t)vio_data.GetData() << std::endl;

    std::cout << "Vio run over timestamp: " << std::to_string(dgraph::TimeUtil::TimeNow()) << std::endl;
  }

  std::uint8_t* raw_image_ = nullptr;
  std::size_t raw_image_size_ = 3840*2160*3/2;
  int64_t timestamp_;
  int64_t time_interval_ = 33000; // 3300ms
};

class Gdc : public Node {
  void run() override {
    std::cout << "Gdc running" << std::endl;

    dgraph::Param* vio_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(VioTopic);
    std::cout << "Gdc get vio image, ptr: " << std::hex << (std::uint64_t)vio_data->GetData() << std::endl;

    timestamp_ = dgraph::TimeUtil::TimeNow();
    dgraph::Param gdc_data;
    gdc_image_ = new std::uint8_t[gdc_image_size_];
    gdc_data.SetData(gdc_image_, gdc_image_size_);
    gdc_data.SetTimestamp(timestamp_);
    gdc_data.SetTopic(GdcTopic);
    dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(GdcTopic, gdc_data);

    std::cout << "Gdc run over, output image, ptr: " << std::hex << (std::uint64_t)gdc_data.GetData() << std::endl;
  }

  std::uint8_t* gdc_image_ = nullptr;
  std::size_t gdc_image_size_ = 1024*576*3/2;
  int64_t timestamp_;
  int64_t time_interval_ = 10000; // 10000ms
};

class VioFree : public Node {
  void run() override {
    std::cout << "Vio Free running\n";
    dgraph::Param* vio_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(VioTopic);
    std::cout << "Vio Free get vio image, ptr: " << std::hex << (std::uint64_t)vio_data->GetData() << std::endl;
    vio_data->Clear();
    dgraph::ParamManager::GetInstance().PopParam<dgraph::Param>(VioTopic);
    std::cout << "VIO Free run over\n";
  }
};

class GdcFree : public Node {
  void run() override {
    std::cout << "Gdc free running" << std::endl;
    dgraph::Param* gdc_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(GdcTopic);
    if (gdc_data == nullptr) {
      std::cout << "Gdc Free get gdc data is nullptr\n";
      std::runtime_error("Gdc Free get gdc data is nullptr");
    }
    if (gdc_data->GetData() == nullptr) {
      std::cout << "Gdc Free get gdc_data GetData is nullptr\n";
      std::runtime_error("Gdc Free get gdc_data GetData is nullptr");
    }
    std::cout << "Gdc Free get gdc image, ptr: " << std::hex << (std::uint64_t)gdc_data->GetData() << std::endl;

    gdc_data->Clear();
    dgraph::ParamManager::GetInstance().PopParam<dgraph::Param>(GdcTopic);
    std::cout << "Gdc free run over" << std::endl;
  }
};

class Pym : public Node {
  void run() override {
    std::cout << "Pym running" << std::endl;

    dgraph::Param* gdc_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(GdcTopic);
    std::cout << "Pym get gdc image, ptr: " << std::hex << (std::uint64_t)gdc_data->GetData() << std::endl;

    timestamp_ = dgraph::TimeUtil::TimeNow();
    dgraph::Param pym_data;
    pym_image_ = new std::uint8_t[pym_image_size_];
    pym_data.SetData(pym_image_, pym_image_size_);
    pym_data.SetTimestamp(timestamp_);
    pym_data.SetTopic(PymTopic);
    dgraph::ParamManager::GetInstance().SetParam<dgraph::Param>(PymTopic, pym_data);

    std::cout << "Pym run over, output image, ptr: " << std::hex << (std::uint64_t)pym_data.GetData() << std::endl;
  }

  std::int64_t timestamp_;
  std::uint8_t* pym_image_ = nullptr;
  std::size_t pym_image_size_ = 1024*576*3/2;
};

class PymFree : public Node {
  void run() override {
    std::cout << "Pym free running" << std::endl;

    dgraph::Param* pym_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(PymTopic);
    std::cout << "Pym Free get pym image, ptr: " << std::hex << (std::uint64_t)pym_data->GetData() << std::endl;
    pym_data->Clear();
    dgraph::ParamManager::GetInstance().PopParam<dgraph::Param>(PymTopic);

    std::cout << "Pym free run over" << std::endl;
  }
};

class H265Input : public Node {
  void run() override {
    std::cout << "H265Input running" << std::endl;
    
    dgraph::Param* gdc_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(GdcTopic);
    std::cout << "H265Input get gdc image, ptr: " << std::hex << (std::uint64_t)gdc_data->GetData() << std::endl;

    std::cout << "H265Input run over" << std::endl;
  }
};

class H265Output : public Node {
  void run() override {
    std::cout << "H265Output running" << std::endl;
    std::cout << "H265Output callback H265, run over" << std::endl;
  }
};

class Roi0 : public Node {
  void run() override {
    std::cout << "ROI0 running" << std::endl;

    dgraph::Param* pym_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(PymTopic);
    std::cout << "Roi0 get gdc image, ptr: " << std::hex << (std::uint64_t)pym_data->GetData() << std::endl;

    std::cout << "ROI0 callback Roi0 output, run over" << std::endl;
  }
};

class Roi1 : public Node {
  void run() override {
    std::cout << "ROI1 running\n";

    dgraph::Param* pym_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(PymTopic);
    std::cout << "Roi1 get gdc image, ptr: " << std::hex << (std::uint64_t)pym_data->GetData() << std::endl;

    std::cout << "ROI1 callback Roi1 output, run over" << std::endl;
  }
};

class Roi2 : public Node {
  void run() override {
    std::cout << "ROI2 running" << std::endl;

    dgraph::Param* pym_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(PymTopic);
    std::cout << "Roi2 get gdc image, ptr: " << std::hex << (std::uint64_t)pym_data->GetData() << std::endl;

    std::cout << "ROI2 callback Roi1 output, run over" << std::endl;
  }
};

class Roi3 : public Node {
  void run() override {
    std::cout << "ROI3 running" << std::endl;

    dgraph::Param* pym_data = dgraph::ParamManager::GetInstance().GetParam<dgraph::Param>(PymTopic);
    std::cout << "Roi3 get gdc image, ptr: " << std::hex << (std::uint64_t)pym_data->GetData() << std::endl;

    std::cout << "ROI3 callback Roi1 output, run over" << std::endl;
  }
};

class Sink : public Node {
  void run() override {
    std::cout << "Sink run over" << std::endl;
  }
};

#endif // FVP_PIPELINES_NODES_H_