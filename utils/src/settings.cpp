#include "utils/include/settings.h"

#include "utils/include/constants.h"

using namespace common_constants;

settings::Settings::Settings()
    : _destination_file_name(kDefaultSignatureFilePath),
      _block_size(kDefaultBlockSize) {}

settings::Settings &settings::Settings::instance() {
  static Settings _instance;
  return _instance;
}

void settings::Settings::set_source_filename(const std::string &filename) {
  std::lock_guard<std::mutex> lock(_sfn_mtx);
  _source_file_name = filename;
}

std::string settings::Settings::get_source_filename() {
  std::lock_guard<std::mutex> lock(_sfn_mtx);
  return _source_file_name;
}

void settings::Settings::set_destination_filename(const std::string &filename) {
  std::lock_guard<std::mutex> lock(_dfn_mtx);
  _destination_file_name = filename;
}

std::string settings::Settings::get_destination_filename() {
  std::lock_guard<std::mutex> lock(_dfn_mtx);
  return _destination_file_name;
}

void settings::Settings::set_block_size(std::size_t block_size) {
  _block_size = block_size;
}

std::size_t settings::Settings::get_block_size() { return _block_size; }

void settings::Settings::set_available_thread_amount(
    std::size_t threads_amount) {
  _available_threads_amount = threads_amount;
}

std::size_t settings::Settings::get_available_thread_amount() {
  return _available_threads_amount;
}

void settings::Settings::set_file_size(std::size_t size) { _file_size = size; }

std::size_t settings::Settings::get_file_size() { return _file_size; }

void settings::Settings::set_read_data_blocks(std::size_t blocks) {
  _read_data_blocks = blocks;
}

std::size_t settings::Settings::get_read_data_blocks_amount() {
  return _read_data_blocks;
}

void settings::Settings::set_generated_hash_blocks(std::size_t blocks) {
  _generated_hash_blocks = blocks;
}

std::size_t settings::Settings::get_generated_hash_blocks_amount() {
  return _generated_hash_blocks;
}

void settings::Settings::set_written_blocks(std::size_t blocks) {
  _written_hash_blocks = blocks;
}

std::size_t settings::Settings::get_written_blocks_amount() {
  return _written_hash_blocks;
}
