#include <iostream>

#include "include/fs_generator.h"
#include "utils/include/log.h"
#include "utils/include/result_printer.h"

int main(int args, const char* argv[]) {
  utils::ResultPrinter result_printer(settings::Settings::instance());
  logger::Logger logger;
  fs_generator::FSGenerator fs_generator;
  if (!fs_generator.init(args, argv)) {
    LOG_ERROR(logger) << "The File Generator initialization failed.";
    return 1;
  }
  fs_generator.generate();

  return 0;
}
