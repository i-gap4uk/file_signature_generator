#include "utils/include/scope_timer.h"

#include <iostream>

namespace utils {
ScopeTimer::ScopeTimer() : _start(std::chrono::high_resolution_clock::now()) {}

ScopeTimer::~ScopeTimer() {
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - _start;
  std::cout << "Completed time: " << duration.count() << "s" << std::endl;
}
}  // namespace utils
