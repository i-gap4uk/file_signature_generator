#ifndef TIMER_H
#define TIMER_H

#include <chrono>

namespace utils {
class ScopeTimer {
 public:
  ScopeTimer();
  ~ScopeTimer();

 private:
  std::chrono::high_resolution_clock::time_point _start;
};
}  // namespace utils

#endif  // TIMER_H
