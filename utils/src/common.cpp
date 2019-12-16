#include "utils/include/common.h"

#include <sstream>
#include <stdexcept>

#include "utils/include/constants.h"

namespace common {
std::size_t calculate_block_size(std::size_t block_size_in_mb) {
  return block_size_in_mb == 0
             ? common_constants::kBytesInMb
             : (common_constants::kBytesInMb * block_size_in_mb);
}

void parse_command_line_arguments(int args, const char* argv[],
                                  std::string& source_file,
                                  std::string& signature_file,
                                  std::size_t& block_size) {
  switch (args) {
    case 0:
    case 1:
      throw std::invalid_argument(
          "Wrong amount of input parameters. Required at least 1, but provided "
          "0. You can't ommit input file parameter.");
      break;
    case 2: {
      source_file = argv[common_constants::InputParameters::INPUT_FILE];
    } break;
    case 3:
      source_file = argv[common_constants::InputParameters::INPUT_FILE];
      signature_file = argv[common_constants::InputParameters::SIGNATURE_FILE];
      break;
    case 4:
      source_file = argv[common_constants::InputParameters::INPUT_FILE];
      signature_file = argv[common_constants::InputParameters::SIGNATURE_FILE];
      block_size =
          std::stoi(argv[common_constants::InputParameters::BLOCK_SIZE]);
      break;
    default:
      throw std::invalid_argument(
          "Wrong amount of input parameters. Allowed maximum 3, but was"
          "provided: " +
          std::to_string(args));
  }
}

std::string accamble_execution_result_string(const std::string& input_file,
                                   const std::string& output_file,
                                   std::size_t file_size_in_bytes,
                                   std::size_t block_size_in_mb,
                                   std::size_t read_blocks,
                                   std::size_t generated_hash_blocks,
                                   std::size_t written_hash_blocks) {
  const unsigned long long bytes_per_kb = 1024ULL;
  const unsigned long long bytes_per_mb = 1024ULL * bytes_per_kb;
  const unsigned long long bytes_per_gb = 1024ULL * bytes_per_mb;

  // Calculating GB, MB, KB
  unsigned long long gigabytes = file_size_in_bytes / bytes_per_gb;
  unsigned long long remaining_after_gb = file_size_in_bytes % bytes_per_gb;

  unsigned long long megabytes = remaining_after_gb / bytes_per_mb;
  unsigned long long remaining_after_mb = remaining_after_gb % bytes_per_mb;

  unsigned long long kilobytes = remaining_after_mb / bytes_per_kb;
  unsigned long long remaining_after_kb = remaining_after_mb % bytes_per_kb;

  std::stringstream ss;
  ss << std::endl;
  ss << "==========================================================\n";
  ss << "Input file path:       " << input_file << std::endl;
  ss << "Ouput file path:       " << output_file << std::endl;
  ss << "File size:             " << gigabytes << " GB : " << megabytes
     << " MB : " << kilobytes << " KB : " << remaining_after_kb << " bytes.\n";
  ss << "Block size in Bytes:   " << block_size_in_mb << std::endl;
  ss << "Read blocks:           " << read_blocks << std::endl;
  ss << "Generated hash blocks: " << generated_hash_blocks << std::endl;
  ss << "Written hash blocks:   " << written_hash_blocks << std::endl;

  ss << "==========================================================\n";
  ss << std::endl;
  return ss.str();
}

}  // namespace common
