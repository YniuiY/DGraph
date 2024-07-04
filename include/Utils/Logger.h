#ifndef DGRAPH_LOGGER_H_
#define DGRAPH_LOGGER_H_

#include <memory>
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace dgraph {  

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

class Logger {
 public:
  static std::shared_ptr<spdlog::logger>& GetLogger();
  static void Init(std::string log_path);
  ~Logger() = default;
 private:
  Logger() = default;
  static std::shared_ptr<spdlog::logger> logger_;
  static std::vector<spdlog::sink_ptr> sinks_;
};

} // namespcae dgraph

#endif // DGRAPH_LOGGER_H_