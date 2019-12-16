#include "include/fs_generator.h"

#include <iostream>
#include <stdexcept>

#include "include/file_manager_impl.h"
#include "include/fs_gen_multithread_impl.h"
#include "include/fs_gen_single_thread_impl.h"
#include "include/resource_manager_impl.h"
#include "utils/include/common.h"
#include "utils/include/constants.h"
#include "utils/include/hash_generator.h"
#include "utils/include/settings.h"

namespace {
using namespace fs_generator;
using namespace settings;
using namespace common_constants;

FSGenImplPtr create_implementation(
    std::shared_ptr<hash_generator::HashGenerator> hash_generator,
    std::shared_ptr<file_manager::FileManager> file_manager,
    std::shared_ptr<resource_manager::ResourceManager> resource_manager) {
  const auto available_threads = std::thread::hardware_concurrency();

  Settings::instance().set_available_thread_amount(available_threads);

  FSGenImplPtr sign_gen_impl;
  return available_threads <= kMinReasonableThreadsAmount
             ? sign_gen_impl = std::make_shared<FSGenSingleThreadImpl>(
                   hash_generator, file_manager)
             : sign_gen_impl = std::make_shared<FSGenMultithreadImpl>(
                   file_manager, resource_manager, hash_generator);
}

}  // namespace

using namespace settings;

namespace fs_generator {

FSGenerator::FSGenerator() : _logger("FSGenerator") {}

bool FSGenerator::init(int args, const char* argv[]) {
  const bool base_param_init_result =
      basic_parameters_initialization(args, argv);

  bool components_init_result = true;
  if (!init_components()) {
    LOG_ERROR(_logger) << "Components initialization was failed.";
    components_init_result = false;
  }

  return components_init_result && base_param_init_result;
}

bool FSGenerator::basic_parameters_initialization(int args,
                                                  const char* argv[]) {
  std::string source_file;
  std::string destination_file;
  std::size_t block_size = 0;

  bool result = true;
  do {
    try {
      common::parse_command_line_arguments(args, argv, source_file,
                                           destination_file, block_size);
    } catch (const std::exception& e) {
      LOG_ERROR(_logger)
          << "File signature generator initialization was failed. The reason: "
          << e.what();
      result = false;
      break;
    }

    if (source_file.empty()) {
      LOG_ERROR(_logger)
          << "The source file did not specified. Generation aborted.";
      result = false;
      break;
    }
    Settings::instance().set_source_filename(source_file);

    if (destination_file.empty()) {
      LOG_WARNING(_logger)
          << "Wrong sginature file path was provided. Will be used "
             "default path: "
          << common_constants::kDefaultSignatureFilePath;
      destination_file = common_constants::kDefaultSignatureFilePath;
    }
    Settings::instance().set_destination_filename(destination_file);

    if (block_size == 0) {
      LOG_WARNING(_logger) << "Wrong block size specified: " << block_size
                           << ". Will be used default block size: "
                           << common_constants::kDefaultBlockSize * kBytesInMb
                           << " bytes";
      block_size = common_constants::kDefaultBlockSize * kBytesInMb;
    } else {
      block_size = common::calculate_block_size(block_size);
    }
    Settings::instance().set_block_size(block_size);

  } while (false);

  return result;
}

bool FSGenerator::init_components() {
  bool init_result = true;
  do {
    _hash_gen = std::make_shared<hash_generator::HashGenerator>();
    _file_man = std::make_shared<file_manager::FileManagerImpl>(
        Settings::instance().get_source_filename(),
        Settings::instance().get_destination_filename());

    if (!_file_man->init()) {
      LOG_ERROR(_logger) << "File manager initialization was failed.";
      init_result = false;
      break;
    }

    _res_man = std::make_shared<resource_manager::ResourceManagerImpl>();
    _fs_gen_impl = create_implementation(_hash_gen, _file_man, _res_man);

  } while (false);

  return init_result;
}

void FSGenerator::generate() {
  try {
    _fs_gen_impl->generate_file_signature();
  } catch (const std::exception& e) {
    LOG_ERROR(_logger) << "Generation was failed. The reason: " << e.what();
  }
}

}  // namespace fs_generator
