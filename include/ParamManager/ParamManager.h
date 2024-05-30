// Author: Di Yang
// Update: 2024-04-12

#ifndef PARAM_MANAGER_H
#define PARAM_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>
#include <queue>

#include "ParamManager/Param.h"
#include "RingBuffer/RingBuffer.h"

namespace dgraph {

class ParamManager {
 public:
  static ParamManager& GetInstance();

  ~ParamManager() = default;

  // 获取参数
  template<class Type>
  Type* GetParam(std::string const& topic) {
    if (param_map_.find(topic) != param_map_.end()) {
      return dynamic_cast<Type*>(param_map_.at(topic).Front());
    } else {
      std::cerr << "ParamManager Not Have " << topic << " Param\n";
      return nullptr;
    }
  }

  template<class Type>
  bool PopParam(std::string const& topic) {
    bool ret{false};

    if (param_map_.find(topic) != param_map_.end()) {
      param_map_.at(topic).Pop();
      ret = true;
    } else {
      std::cerr << "ParamManager Not Have " << topic << " Param\n";
    }

    return ret;
  }

  // 获取可修改参数
  template<class Type>
  Type* GetMultableParam(std::string const& topic) {
    if (param_map_.find(topic) != param_map_.end()) {
      return dynamic_cast<Type*>(param_map_.at(topic).Front());
    } else {
      std::cerr << "ParamManager Not Have " << topic << " Param\n";
      return nullptr;
    }
  }

  // 设置参数
  template<class Type>
  void SetParam(std::string const& topic, Param const& param) {
    param_map_[topic].Push(param);
  }


 private:
  ParamManager() = default;
  /// @brief pair<topic, queue<param>>
  std::unordered_map<std::string, RingBuffer<Param, 180>> param_map_;
};

} // namespace dgraph
#endif // PARAM_MANAGER_H
