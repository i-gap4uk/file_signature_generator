/**
 * Developed by Igor Gapchuk
 * 2019
 */

#ifndef INCLUDE_FILE_MANGER_H
#define INCLUDE_FILE_MANGER_H

#include <memory>
#include <string>
#include <vector>
#include <cstdint>

#include "utils/include/types.h"
#include "utils/include/constants.h"

namespace file_manager {


class FileManager {
 public:

  virtual bool init() = 0;
  virtual common_constants::READING_RESULT read_data(common_types::DataContainer& data_block) = 0;
  virtual void write_hash_to_file(const std::string& hash_string) = 0;

  virtual ~FileManager() {}
};


using FMPtr = std::shared_ptr<FileManager>;
}  // namespace file_manager

#endif  // INCLUDE_FILE_MANGER_H
