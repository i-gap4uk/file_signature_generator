#ifndef COMMON
#define COMMON

#include <cstdint>
#include <string>

namespace common {

std::size_t calculate_block_size(std::size_t block_size_in_mb);
void parse_command_line_arguments(int args, const char* argv[],
                                  std::string& source_file,
                                  std::string& signature_file,
                                  std::size_t& block_size);

std::string accamble_execution_result_string(const std::string& input_file,
                                   const std::string& output_file,
                                   std::size_t file_size_in_bytes,
                                   std::size_t block_size_in_mb,
                                   std::size_t read_blocks,
                                   std::size_t generated_hash_blocks,
                                   std::size_t written_hash_blocks);

}  // namespace common

#endif  // COMMON
