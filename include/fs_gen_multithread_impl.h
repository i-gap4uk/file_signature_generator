#ifndef INCLUDE_FILE_SIGNATURE_HANDLER_IMPL_H
#define INCLUDE_FILE_SIGNATURE_HANDLER_IMPL_H

#include <atomic>
#include <condition_variable>
#include <cstdint>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include "core/log.h"
#include "interfaces/fs_gen_impl.h"
#include "utils/include/types.h"

namespace file_manager {
class FileManager;
}

namespace resource_manager {
class ResourceManager;
}
namespace hash_generator {
class HashGenerator;
}

using FManPtr = std::shared_ptr<file_manager::FileManager>;
using HGenPtr = std::shared_ptr<hash_generator::HashGenerator>;
using RMPtr = std::shared_ptr<resource_manager::ResourceManager>;

namespace fs_generator {

class FSGenMultithreadImpl : public IFSGenImpl {
 public:
  FSGenMultithreadImpl(FManPtr file_manager, RMPtr resource_manager,
                       HGenPtr hash_generator);

  void generate_file_signature() override;
  void abort_generation() override;

  ~FSGenMultithreadImpl();

 private:
  void init_and_run_threads();

  void read_data();
  void generate_hash();
  void write_hash();

  void push_data(const common_types::DataContainer& data);
  common_types::DataContainer get_data();

  void push_hash(const common_types::HashContainer& hash);
  common_types::HashContainer get_hash();

  bool generating_threads_completed();
  void set_thread_status(std::thread::id thread_id, bool status);

  FManPtr _file_man;
  RMPtr _res_man;
  HGenPtr _hash_gen;

  // File manager completed to read data from a file.
  std::atomic<bool> _data_reading_completed;

  // Hash generator generated hashes from all data blocks.
  std::atomic<bool> _hash_generating_completed;

  // All hash blocks are written into a file.
  std::atomic<bool> _hash_writing_completed;

  std::size_t _available_threads_amount;
  std::thread _read_thread;
  std::vector<std::thread> _work_threads;
  std::thread _write_thread;

  std::mutex _push_hash_mtx;
  std::condition_variable _push_hash_cv;

  std::mutex _push_data_mtx;
  std::condition_variable _push_data_cv;

  std::mutex _hash_writing_mtx;
  std::condition_variable _hash_writing_cv;

  std::atomic<bool> _is_running;

  std::map<std::thread::id, bool> _threads_running_status;
  std::mutex _threads_status_mtx;

  logger::Logger _logger;
};

}  // namespace fs_generator

#endif  // INCLUDE_FILE_SIGNATURE_HANDLER_IMPL_H
