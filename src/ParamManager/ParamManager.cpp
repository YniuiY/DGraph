#include "ParamManager/ParamManager.h"
#include <iostream>

namespace dgraph {

ParamManager& ParamManager::GetInstance() {
  static ParamManager instance{ParamManager()};
  return instance;
}

} // namespace dgraph