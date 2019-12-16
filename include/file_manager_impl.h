#ifndef SRC_FILE_MANAGER_IMPL_H
#define SRC_FILE_MANAGER_IMPL_H

#include <fstream>
#include <mutex>

#include "include/interfaces/file_manager.h"
#include "utils/include/constants.h"
#include "utils/include/log.h"
#include "utils/include/types.h"

namespace file_manager {
class FileManagerImpl : public FileManager {
 public:
  FileManagerImpl(const std::string& input_file,
                  const std::string& output_file);

  bool init() override;

  common_constants::READING_RESULT read_data(
      common_types::DataContainer& data_container) override;

  void write_hash_to_file(const std::string& hash_string) override;

  ~FileManagerImpl() override;

 private:
  bool open_input_file();
  bool open_output_file();

  void finalaize();

  void close_input_file();
  void close_output_file();

  std::size_t calculate_file_size();

  std::size_t _already_read_size;

  std::size_t _data_block_id;

  const std::string _input_file_path;
  const std::string _output_file_path;

  std::ifstream _input_stream;
  std::ofstream _output_steam;

  logger::Logger _logger;
};
}  // namespace file_manager

#endif  // SRC_FILE_MANAGER_IMPL_H
