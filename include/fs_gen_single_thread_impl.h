#ifndef FSGENSINGLETHREADIMPL_H
#define FSGENSINGLETHREADIMPL_H

#include <memory>

#include "core/log.h"
#include "interfaces/fs_gen_impl.h"

namespace hash_generator {
class HashGenerator;
}

namespace file_manager {
class FileManager;
}

namespace fs_generator {
class FSGenSingleThreadImpl : public IFSGenImpl {
 public:
  FSGenSingleThreadImpl(
      std::shared_ptr<hash_generator::HashGenerator> hash_generator,
      std::shared_ptr<file_manager::FileManager> fm);

  void generate_file_signature() override;
  void abort_generation() override;

 private:
  std::shared_ptr<hash_generator::HashGenerator> _hash_generator;
  std::shared_ptr<file_manager::FileManager> _file_manager;

  bool _is_running;
  logger::Logger _logger;
};
}  // namespace fs_generator

#endif  // FSGENSINGLETHREADIMPL_H
