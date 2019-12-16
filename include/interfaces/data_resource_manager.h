#ifndef INCLUDE_INTERFACES_DATA_RESOURCE_MANAGER_H
#define INCLUDE_INTERFACES_DATA_RESOURCE_MANAGER_H

#include "utils/include/types.h"

namespace data_resource_manager {

class IDataResourceManager {
 public:
    
    virtual void push_data(const common_types::DataContainer& data_block) = 0;
    virtual bool is_data_storage_empty() = 0;
    virtual common_types::DataContainer get_data() = 0;
    virtual std::size_t get_last_block_id() = 0;

  virtual ~IDataResourceManager() {}
};

}  // namespace data_resource_manager

#endif  // INCLUDE_INTERFACES_DATA_RESOURCE_MANAGER_H
