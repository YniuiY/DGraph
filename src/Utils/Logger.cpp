#include "Utils/Logger.h"

#include <vector>
#include <iostream>

namespace dgraph {

std::vector<spdlog::sink_ptr> Logger::sinks_;
std::shared_ptr<spdlog::logger> Logger::logger_;

std::shared_ptr<spdlog::logger>& Logger::GetLogger() {
  return logger_;
}

void Logger::Init(std::string log_path) {
  auto max_size = 1048576 * 5;  // 5MB
  auto max_files = 2;
  auto rotating_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_path, max_size, max_files);
  auto stdout_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
  sinks_.push_back(rotating_sink);
  sinks_.push_back(stdout_sink);
  logger_ = std::make_shared<spdlog::logger>(log_path, sinks_.begin(), sinks_.end());
  logger_->set_level(spdlog::level::debug);
  logger_->set_pattern("[%Y-%m-%d %H:%M:%S.%e.%f][%^%L%$] [tid %t] %v");
  logger_->flush_on(spdlog::level::debug);
  logger_->debug("Logger initialized");
}

} // namespace dgraph