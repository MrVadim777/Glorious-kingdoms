#pragma once
#include <chrono>
#include <string>
#include <unordered_map>

class DebugProfilerTimer {
  private:
    using Clock = std::chrono::steady_clock;

    static inline std::unordered_map<std::string, Clock::time_point> startTimes;
    static inline std::unordered_map<std::string, float>             timings;

  public:
    static void begin(const std::string& label) {
        startTimes[label] = Clock::now();
    }

    static void end(const std::string& label) {
        auto end = Clock::now();
        float duration = std::chrono::duration<float, std::milli>(end - startTimes[label]).count();

        timings[label] = duration;
    }

    static float getTime(const std::string& label) {
        auto it = timings.find(label);
        if (it != timings.end()) {
            return it->second;
        }
        return 0.f;
    }

    static const std::unordered_map<std::string, float>& getAllTimings() {
        return timings;
    }

    static void clear() {
        timings.clear();
    }
};
