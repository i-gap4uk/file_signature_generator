#include "include/file_manager_impl.h"

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "utils/include/settings.h"

namespace file_manager {

using namespace common_types;
using namespace common_constants;

FileManagerImpl::FileManagerImpl(const std::string& input_file,
                                 const std::string& output_file)
    : _already_read_size(0),
      _data_block_id(0),
      _input_file_path(input_file),
      _output_file_path(output_file),
      _logger("FileManager") {}

bool FileManagerImpl::init() {
  bool if_opened = false;
  bool of_opened = false;
  do {
    try {
      if_opened = open_input_file();
    } catch (const std::exception& e) {
      LOG_ERROR(_logger) << "Input file opening failed. The reason: "
                         << e.what();
      LOG_ERROR(_logger) << "Input file: " << _input_file_path;
      if_opened = false;
      break;
    }

    settings::Settings::instance().set_file_size(calculate_file_size());

    try {
      of_opened = open_output_file();
    } catch (const std::exception& e) {
      LOG_ERROR(_logger) << "Output file opening was failed. The reason: "
                         << e.what();
      of_opened = false;
      break;
    }
  } while (false);

  LOG_INFO(_logger) << "Initialization successfully: " << std::boolalpha
                    << (if_opened && of_opened);

  return if_opened && of_opened;
}

READING_RESULT FileManagerImpl::read_data(DataContainer& data_container) {
  try {
    data_container.clear();

    data_container.id = ++_data_block_id;
    const auto remining_size =
        settings::Settings::instance().get_file_size() - _already_read_size;

    if (remining_size < settings::Settings::instance().get_block_size()) {
      // The case when file data size less than the specified block
      // size. Data block should have size as size for hashing block and
      // remaining space should be filled by zero.

      _input_stream.read(data_container.data.data(),
                         static_cast<long>(remining_size));

      return READING_RESULT::END_OF_FILE;
    }

    if (_input_stream.good()) {
      _input_stream.read(data_container.data.data(),
                         data_container.data.size());
    }

    _already_read_size += static_cast<std::size_t>(_input_stream.gcount());

    return _already_read_size >= settings::Settings::instance().get_file_size()
               ? READING_RESULT::END_OF_FILE
               : READING_RESULT::COMPLETED;

  } catch (const std::ios_base::failure& e) {
    LOG_ERROR(_logger) << "Reading file error. Reason: " << e.what();
    LOG_ERROR(_logger) << "File path: " << _input_file_path;
    finalaize();
    throw std::runtime_error(e.what());
  }
}

void FileManagerImpl::write_hash_to_file(const std::string& hash_string) {
  try {
    long buffer_size = static_cast<long>(hash_string.size());
    _output_steam.write(hash_string.c_str(), buffer_size);
  } catch (const std::exception& e) {
    LOG_ERROR(_logger) << "Writing hash failed! Reason: " << e.what();
    finalaize();
    throw e;
  }
}

FileManagerImpl::~FileManagerImpl() { finalaize(); }

bool FileManagerImpl::open_input_file() {
  _input_stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  _input_stream.open(_input_file_path, std::ifstream::binary);
  return _input_stream.is_open();
}

bool FileManagerImpl::open_output_file() {
  _output_steam.exceptions(std::ofstream::failbit | std::ofstream::badbit);
  _output_steam.open(_output_file_path,
                     std::ofstream::out | std::ofstream::trunc);
  return _output_steam.is_open();
}

void FileManagerImpl::finalaize() {
  close_input_file();
  close_output_file();
}

void FileManagerImpl::close_input_file() {
  if (_input_stream.is_open()) {
    _input_stream.close();
    LOG_DEBUG(_logger) << "Input file closed.";
  }
}

void FileManagerImpl::close_output_file() {
  if (_output_steam.is_open()) {
    _output_steam.close();
    LOG_DEBUG(_logger) << "Output file closed.";
  }
}

std::size_t FileManagerImpl::calculate_file_size() {
  _input_stream.seekg(0, std::ios::end);
  std::size_t file_size = static_cast<std::size_t>(_input_stream.tellg());
  _input_stream.seekg(0, std::ios::beg);
  return file_size;
}

}  // namespace file_manager
