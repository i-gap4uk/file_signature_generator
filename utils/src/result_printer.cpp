#include "utils/include/result_printer.h"

#include <iostream>

#include "utils/include/common.h"

namespace utils {

ResultPrinter::ResultPrinter(settings::Settings& settings)
    : _settings(settings) {}

ResultPrinter::~ResultPrinter() {
  LOG_DEBUG(_logger) << common::accamble_execution_result_string(
      _settings.get_source_filename(), _settings.get_destination_filename(),
      _settings.get_file_size(), _settings.get_block_size(),
      _settings.get_read_data_blocks_amount(),
      _settings.get_generated_hash_blocks_amount(),
      _settings.get_written_blocks_amount());
}

}  // namespace utils
