#pragma once
#include "DebugProfilerTimer.h"
#include <string>

class DebugProfileScope {
  private:
    std::string label;

  public:
    DebugProfileScope(const std::string& name) : label(name) {
        DebugProfilerTimer::begin(label);
    }

    ~DebugProfileScope() {
        DebugProfilerTimer::end(label);
    }
};

#define PROFILE_SCOPE(name) DebugProfileScope _scope_##__LINE__{name};
