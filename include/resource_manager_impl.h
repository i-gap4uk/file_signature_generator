#ifndef SRC_RESOURCE_MANAGER_IMPL_H
#define SRC_RESOURCE_MANAGER_IMPL_H

#include <mutex>

#include "include/interfaces/resource_manager.h"
#include "utils/include/types.h"

namespace resource_manager {
class ResourceManagerImpl : public ResourceManager {
 public:
  ResourceManagerImpl();
  ~ResourceManagerImpl() override;

  void push_data(const common_types::DataContainer& data_block) override;
  bool is_data_storage_empty() override;
  common_types::DataContainer get_data() override;
  std::size_t get_last_block_id() override;

  void push_hash(const common_types::HashContainer& hash) override;
  bool is_hash_storage_empty() override;
  common_types::HashContainer get_hash() override;
  std::size_t get_last_hash_id() override;

 private:
  common_types::DataQueue _data_queue;
  common_types::HashQueue _hash_queue;

  std::size_t _last_data_block_id;
  std::size_t _last_hash_id;

  std::mutex _data_id_mtx;
  std::mutex _data_queue_mtx;
  std::mutex _hash_id_mtx;
  std::mutex _hash_queue_mtx;
};

}  // namespace resource_manager

#endif  // SRC_RESOURCE_MANAGER_IMPL_H
