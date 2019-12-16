#ifndef SETTINGS_H
#define SETTINGS_H

#include <atomic>
#include <cstdint>
#include <mutex>
#include <string>

namespace settings {
class Settings {
 public:
  Settings(const Settings& other) = delete;
  Settings& operator=(const Settings& other) = delete;

  static Settings& instance();

  void set_source_filename(const std::string& filename);
  std::string get_source_filename();

  void set_destination_filename(const std::string& filename);
  std::string get_destination_filename();

  void set_block_size(std::size_t block_size);
  std::size_t get_block_size();

  void set_available_thread_amount(std::size_t threads_amount);
  std::size_t get_available_thread_amount();

  void set_file_size(std::size_t size);
  std::size_t get_file_size();

  void set_read_data_blocks(std::size_t blocks);
  std::size_t get_read_data_blocks_amount();

  void set_generated_hash_blocks(std::size_t blocks);
  std::size_t get_generated_hash_blocks_amount();

  void set_written_blocks(std::size_t blocks);
  std::size_t get_written_blocks_amount();

 private:
  Settings();

  std::atomic<std::size_t> _available_threads_amount;

  std::string _source_file_name;
  std::mutex _sfn_mtx;

  std::string _destination_file_name;
  std::mutex _dfn_mtx;

  std::atomic<std::size_t> _block_size;
  std::atomic<unsigned long long> _file_size;

  std::atomic<std::size_t> _read_data_blocks;
  std::atomic<std::size_t> _generated_hash_blocks;
  std::atomic<std::size_t> _written_hash_blocks;
};
}  // namespace settings

#endif  // SETTINGS_H
