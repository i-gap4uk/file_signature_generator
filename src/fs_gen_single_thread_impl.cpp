#include "include/fs_gen_single_thread_impl.h"

#include <iostream>

#include "include/interfaces/file_manager.h"
#include "utils/include/constants.h"
#include "utils/include/hash_generator.h"
#include "utils/include/settings.h"
#include "utils/include/types.h"

using namespace settings;
using namespace file_manager;

namespace fs_generator {

using namespace common_constants;
using namespace common_types;
using namespace logger;

FSGenSingleThreadImpl::FSGenSingleThreadImpl(
    std::shared_ptr<hash_generator::HashGenerator> hash_generator, FMPtr fm)
    : _hash_generator(hash_generator),
      _file_manager(fm),
      _is_running(false),
      _logger("FSGenSingleThreadImpl") {}

void FSGenSingleThreadImpl::generate_file_signature() {
  DataContainer data_container(Settings::instance().get_block_size());

  READING_RESULT read_result = READING_RESULT::INVALID;
  _is_running = true;

  while (_is_running && read_result != READING_RESULT::END_OF_FILE) {
    data_container.clear();

    try {
      read_result = _file_manager->read_data(data_container);
    } catch (const std::exception& e) {
      LOG_ERROR(_logger) << "Unexpected reading data error. The reason: "
                         << e.what();
      throw std::runtime_error(e.what());
    }

    if (data_container.data.empty()) {
      throw std::runtime_error("The data is empty after reading.");
    }

    HashContainer hash_container =
        _hash_generator->generate_hash(data_container.data);
    _file_manager->write_hash_to_file(hash_container.hash);
  }

  LOG_INFO(_logger) << "File signature generating is completed.";
}

void FSGenSingleThreadImpl::abort_generation() { _is_running = false; }

}  // namespace fs_generator
