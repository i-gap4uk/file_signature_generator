#ifndef INCLUDE_INTERFACES_RESOURCE_MANAGER_H
#define INCLUDE_INTERFACES_RESOURCE_MANAGER_H

#include <memory>
#include <cstdint>

#include "include/interfaces/data_resource_manager.h"
#include "include/interfaces/hash_resource_manager.h"


namespace resource_manager {

class ResourceManager : public data_resource_manager::IDataResourceManager,
                        public hash_resource_manager::IHashResourceManager {
 public:
    void push_data(const common_types::DataContainer& data_block) override = 0;
    bool is_data_storage_empty() override = 0;
    common_types::DataContainer get_data() override = 0;
    std::size_t get_last_block_id() override = 0;

    void push_hash(const common_types::HashContainer& hash) override = 0;
    bool is_hash_storage_empty() override = 0;
    common_types::HashContainer get_hash() override = 0;
    std::size_t get_last_hash_id() override = 0;

  ~ResourceManager() override {}
};

using RMPtr = std::shared_ptr<ResourceManager>;
}  // namespace resource_manager

#endif  // INCLUDE_INTERFACES_RESOURCE_MANAGER_H
