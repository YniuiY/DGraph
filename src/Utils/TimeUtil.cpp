#include "Utils/TimeUtil.h"

namespace dgraph {

int64_t TimeUtil::TimeNow() {
  /// @brief 获取当前时间相对于1970.01.01:00:00时刻的时间跨度，单位是us
  /// @return 返回时间跨度
  auto now{std::chrono::system_clock::now()};
  auto tmp{std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch())};
  return tmp.count();
}

} // dgraph