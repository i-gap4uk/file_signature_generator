#ifndef INCLUDE_INTERFACES_HASH_RESOURCE_MANAGER_H
#define INCLUDE_INTERFACES_HASH_RESOURCE_MANAGER_H

#include "utils/include/types.h"

namespace hash_resource_manager {

class IHashResourceManager {
 public:
    
    virtual void push_hash(const common_types::HashContainer& hash) = 0;
     virtual bool is_hash_storage_empty() = 0;
     virtual common_types::HashContainer get_hash() = 0;
     virtual std::size_t get_last_hash_id() = 0;

  virtual ~IHashResourceManager() {}
};
}  // namespace hash_resource_manager

#endif  // INCLUDE_INTERFACES_HASH_RESOURCE_MANAGER_H
