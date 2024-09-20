#ifndef FILE_SIGNATURE_GENERATOR
#define FILE_SIGNATURE_GENERATOR

#include <memory>
#include <string>

#include "core/log.h"

namespace fs_generator {
class IFSGenImpl;
}

namespace hash_generator {
class HashGenerator;
}

namespace file_manager {
class FileManager;
}

namespace resource_manager {
class ResourceManager;
}

using FManPtr = std::shared_ptr<file_manager::FileManager>;
using ResManPtr = std::shared_ptr<resource_manager::ResourceManager>;
using HGenPtr = std::shared_ptr<hash_generator::HashGenerator>;
using FSGenImplPtr = std::shared_ptr<fs_generator::IFSGenImpl>;

namespace fs_generator {
class FSGenerator {
 public:
  FSGenerator();
  ~FSGenerator() = default;

  void generate();

  bool init(int args, const char* argv[]);

 private:
  bool basic_parameters_initialization(int args, const char* argv[]);
  bool init_components();

 private:
  FSGenImplPtr _fs_gen_impl;
  HGenPtr _hash_gen;
  ResManPtr _res_man;
  FManPtr _file_man;
  logger::Logger _logger;
};
}  // namespace fs_generator

#endif  // FILE_SIGNATURE_GENERATOR
