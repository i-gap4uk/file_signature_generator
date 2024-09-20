#ifndef RESULT_PRINTER_H
#define RESULT_PRINTER_H

#include <memory>

#include "core/log.h"
#include "utils/include/scope_timer.h"
#include "utils/include/settings.h"

namespace utils {
class ResultPrinter {
 public:
  ResultPrinter(settings::Settings& settings);
  ~ResultPrinter();

 private:
  ScopeTimer _timer;
  logger::Logger _logger;
  settings::Settings& _settings;
};
}  // namespace utils

#endif  // RESULT_PRINTER_H
