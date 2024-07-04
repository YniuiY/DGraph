#include <iostream>
#include <functional>
#include "DGraph.h"
#include "FvpPipelineNodes.h"
#include "Region/Region.h"

int main() {
  try {
    dgraph::Logger::Init("logs/fvp-pipeline.log");
    auto logger{dgraph::Logger::GetLogger()};

    logger->debug("Starting FVP pipeline");
    Node* vio = nullptr;
    Node* vio_free = nullptr;
    Node* gdc = nullptr;
    Node* pym = nullptr;
    Node* h265_input = nullptr;
    Node* h265_output = nullptr;
    Node* gdc_free = nullptr;
    Node* pym_free = nullptr;
    Node* roi0 = nullptr;
    Node* roi1 = nullptr;
    Node* roi2 = nullptr;
    Node* roi3 = nullptr;
    Node* sink = nullptr;

    std::shared_ptr<DGraph> graph = std::make_shared<DGraph>();
    graph->RegisterNode<Vio>(vio, {}, "Vio");
    graph->RegisterNode<Gdc>(gdc, {vio}, "Gdc");
    graph->RegisterNode<VioFree>(vio_free, {gdc}, "VioFree");
    graph->RegisterNode<Pym>(pym, {vio_free}, "Pym");
    graph->RegisterNode<H265Input>(h265_input, {vio_free}, "H265Input");
    graph->RegisterNode<GdcFree>(gdc_free, {h265_input, pym}, "GdcFree");
    graph->RegisterNode<H265Output>(h265_output, {h265_input}, "H265Output");
    graph->RegisterNode<Roi0>(roi0, {pym}, "Roi0");
    graph->RegisterNode<Roi1>(roi1, {pym}, "Roi1");
    graph->RegisterNode<Roi2>(roi2, {pym}, "Roi2");
    graph->RegisterNode<Roi3>(roi3, {pym}, "ROI3");
    graph->RegisterNode<PymFree>(pym_free, {roi0, roi1, roi2, roi3}, "PymFree");
    graph->RegisterNode<Sink>(sink, {gdc_free, pym_free, h265_output}, "Sink");

    graph->Init();
    graph->Run();
    graph->Deinit();

    logger->debug("FVP pipeline finished");
    return 0;
  } catch (std::exception const& e) {
    std::cerr << e.what() << std::endl;
    return -1;
  }
}