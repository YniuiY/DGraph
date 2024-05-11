// Author: Di Yang
// Update: 2024-04-12

#ifndef PARAM_MANAGER_H
#define PARAM_MANAGER_H

#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <memory>

#include "ParamManager/Param.h"

namespace dgraph {

class ParamManager {
 public:
  static ParamManager& GetInstance();

  ~ParamManager() = default;

  // 获取参数
  template<class Type>
  Type const* GetParam(std::string const& topic) const {
    if (param_map_.find(topic) != param_map_.end()) {
      return dynamic_cast<Type*>(param_map_.at(topic).get());
    } else {
      std::cerr << "ParamManager Not Have " << topic << " Param\n";
      return nullptr;
    }
  }

  // 获取可修改参数
  template<class Type>
  Type* GetMultableParam(std::string const& topic) const {
    if (param_map_.find(topic) != param_map_.end()) {
      return dynamic_cast<Type*>(param_map_.at(topic).get());
    } else {
      std::cerr << "ParamManager Not Have " << topic << " Param\n";
      return nullptr;
    }
  }

  // 设置参数
  template<class Type>
  void SetParam(std::string const& topic, std::shared_ptr<Param> const& param) {
    if (param != nullptr) {
      param_map_[topic] = param;
    } else {
      std::cerr << "Set topic: " << topic << ", Param is nullptr\n";
    }
  }


 private:
  ParamManager() = default;
  /// @brief pair<topic, param>
  std::unordered_map<std::string, std::shared_ptr<Param>> param_map_;
};

} // namespace dgraph
#endif // PARAM_MANAGER_H
