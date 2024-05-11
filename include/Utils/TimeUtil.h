#ifndef TIMEUTIL_H_
#define TIMEUTIL_H_

#include <chrono>
#include <cstdint>

// 获取当前时间单位是毫秒
namespace dgraph {

class TimeUtil {
 public:
  static uint64_t TimeNow();
};

}// dgraph


#endif // TIMEUTIL_H_