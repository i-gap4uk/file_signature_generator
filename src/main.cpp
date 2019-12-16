#include <iostream>

#include "include/fs_generator.h"
#include "utils/include/result_printer.h"

int main(int args, const char* argv[]) {
  utils::ResultPrinter result_printer(settings::Settings::instance());
  fs_generator::FSGenerator fs_generator;
  if (!fs_generator.init(args, argv)) {
    std::cout << "The File Generator initialization was failed." << std::endl;
    return 1;
  }
  fs_generator.generate();

  return 0;
}
