#include "include/fs_gen_multithread_impl.h"

#include <algorithm>
#include <iostream>
#include <stdexcept>

#include "include/interfaces/file_manager.h"
#include "include/interfaces/resource_manager.h"
#include "utils/include/hash_generator.h"
#include "utils/include/settings.h"

// namespace

namespace fs_generator {
using namespace settings;
using namespace common_types;
using namespace common_constants;

FSGenMultithreadImpl::FSGenMultithreadImpl(FManPtr file_manager,
                                           RMPtr resource_manager,
                                           HGenPtr hash_generator)
    : _file_man(file_manager),
      _res_man(resource_manager),
      _hash_gen(hash_generator),
      _data_reading_completed(false),
      _hash_generating_completed(false),
      _hash_writing_completed(false),
      _available_threads_amount(
          Settings::instance().get_available_thread_amount()),
      _is_running(false),
      _logger("FSGenMultithreadImpl") {}

void FSGenMultithreadImpl::generate_file_signature() { init_and_run_threads(); }

void FSGenMultithreadImpl::abort_generation() { _is_running = false; }

FSGenMultithreadImpl::~FSGenMultithreadImpl() {
  if (_read_thread.joinable()) {
    _read_thread.join();
  }

  for (auto& thread : _work_threads) {
    if (thread.joinable()) {
      thread.join();
    }
  }

  if (_write_thread.joinable()) {
    _write_thread.join();
  }
}

void FSGenMultithreadImpl::init_and_run_threads() {
  _is_running = true;

  _read_thread = std::thread(&FSGenMultithreadImpl::read_data, this);

  // Book one thread for writing, one for the reading and leave another one for
  // systems needs
  const auto work_threads_amount = _available_threads_amount - 3;
  for (std::size_t i = 0; i < work_threads_amount; ++i) {
    _work_threads.emplace_back(&FSGenMultithreadImpl::generate_hash, this);
    set_thread_status(_work_threads[_work_threads.size() - 1].get_id(), false);
  }

  _write_thread = std::thread(&FSGenMultithreadImpl::write_hash, this);
}

void FSGenMultithreadImpl::read_data() {
  DataContainer data_container(Settings::instance().get_block_size());
  auto result = READING_RESULT::INVALID;

  while (_is_running && READING_RESULT::END_OF_FILE != result) {
    result = _file_man->read_data(data_container);
    push_data(data_container);
    LOG_DEBUG(_logger) << "Pushed data block id: " << data_container.id;
    data_container.clear();
  }

  settings::Settings::instance()
      .settings::Settings::instance()
      .set_read_data_blocks(_res_man->get_last_block_id());

  _data_reading_completed = true;
  _push_data_cv.notify_all();

  LOG_INFO(_logger) << "Data reading completed.";
}

void FSGenMultithreadImpl::generate_hash() {
  while (_is_running && !_hash_generating_completed) {
    if (_res_man->is_data_storage_empty() && !_data_reading_completed) {
      // dara reading in the progress, need to wait a new data block
      std::unique_lock<std::mutex> lock(_push_data_mtx);
      _push_data_cv.wait(lock, [this]() {
        return !_res_man->is_data_storage_empty() || _data_reading_completed;
      });
    }

    if (_res_man->is_data_storage_empty() && _data_reading_completed) {
      // data reading is completed. no more data for hash geneating
      set_thread_status(std::this_thread::get_id(), true);
      break;
    }

    const DataContainer data = get_data();
    if (!data.is_valid()) {
      LOG_DEBUG(_logger) << "Data empty, nothig to generate. Skip.";
      continue;
    }

    HashContainer hash;
    try {
      hash = _hash_gen->generate_hash(data.data);
    } catch (std::exception& e) {
      LOG_ERROR(_logger) << "Hash generating aborted. Reason: " << e.what();
      abort_generation();
    }

    push_hash(hash);
    _hash_writing_cv.notify_one();
    LOG_DEBUG(_logger) << "Pushed hash block id: " << hash.id;
  }

  _hash_generating_completed = generating_threads_completed();
  _hash_writing_cv.notify_one();

  settings::Settings::instance().set_generated_hash_blocks(
      _res_man->get_last_hash_id());

  LOG_INFO(_logger) << "Generating hash is completed";
}

void FSGenMultithreadImpl::write_hash() {
  std::size_t written_blocks = 0;

  while (_is_running && !_hash_writing_completed) {
    HashContainer hash_container = get_hash();

    if (!hash_container.is_valid() && !_hash_generating_completed) {
      continue;
    }

    if (hash_container.is_valid()) {
      _file_man->write_hash_to_file(hash_container.hash);
      ++written_blocks;
    }
    hash_container.clear();

    _hash_writing_completed =
        _res_man->is_hash_storage_empty() && _hash_generating_completed;
  }

  settings::Settings::instance().set_written_blocks(written_blocks);
  LOG_INFO(_logger) << "Writing hash is completed";
}

void FSGenMultithreadImpl::push_data(const common_types::DataContainer& data) {
  _res_man->push_data(data);
  _push_data_cv.notify_all();
}

common_types::HashContainer FSGenMultithreadImpl::get_hash() {
  return _res_man->get_hash();
}

bool FSGenMultithreadImpl::generating_threads_completed() {
  std::lock_guard<std::mutex> lock(_threads_status_mtx);
  return std::all_of(
      _threads_running_status.begin(), _threads_running_status.end(),
      [](const auto& thread_status) { return thread_status.second; });
}

void FSGenMultithreadImpl::set_thread_status(std::thread::id thread_id,
                                             bool status) {
  std::lock_guard<std::mutex> lock(_threads_status_mtx);
  _threads_running_status[thread_id] = status;
}

common_types::DataContainer FSGenMultithreadImpl::get_data() {
  return _res_man->get_data();
}

void FSGenMultithreadImpl::push_hash(const common_types::HashContainer& hash) {
  std::unique_lock<std::mutex> lock(_push_hash_mtx);

  if (_res_man->get_last_hash_id() != (hash.id - 1)) {
    _push_hash_cv.wait(lock, [this, hash]() {
      return hash.id == (_res_man->get_last_hash_id() + 1);
    });
  }

  _res_man->push_hash(hash);
  _push_hash_cv.notify_all();
}

}  // namespace fs_generator
