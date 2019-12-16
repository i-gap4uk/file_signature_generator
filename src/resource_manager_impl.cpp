#include "include/resource_manager_impl.h"

namespace resource_manager {

using namespace common_types;

ResourceManagerImpl::ResourceManagerImpl()
    : _last_data_block_id(0), _last_hash_id(0) {}

ResourceManagerImpl::~ResourceManagerImpl() {}

void ResourceManagerImpl::push_data(const DataContainer& data_block) {
  {
    std::lock_guard<std::mutex> lock(_data_queue_mtx);
    _data_queue.push(data_block);
  }
  {
    std::lock_guard<std::mutex> lock(_data_id_mtx);
    _last_data_block_id = data_block.id;
  }
}

void ResourceManagerImpl::push_hash(const HashContainer& hash) {
  {
    std::lock_guard<std::mutex> lock(_hash_queue_mtx);
    _hash_queue.push(hash);
  }
  {
    std::lock_guard<std::mutex> lock(_hash_id_mtx);
    _last_hash_id = hash.id;
  }
}

bool ResourceManagerImpl::is_hash_storage_empty() {
  std::lock_guard<std::mutex> lock(_hash_queue_mtx);
  return _hash_queue.empty();
}

HashContainer ResourceManagerImpl::get_hash() {
  std::lock_guard<std::mutex> lock(_hash_queue_mtx);
  HashContainer hash;
  hash.id = HashContainer::kInvalidId;

  if (_hash_queue.empty()) {
    return hash;
  }

  hash = _hash_queue.front();
  _hash_queue.pop();

  return hash;
}

std::size_t ResourceManagerImpl::get_last_hash_id() {
  std::lock_guard<std::mutex> lock(_hash_id_mtx);
  return _last_hash_id;
}

bool ResourceManagerImpl::is_data_storage_empty() {
  std::lock_guard<std::mutex> lock(_data_queue_mtx);
  return _data_queue.empty();
}

DataContainer ResourceManagerImpl::get_data() {
  std::lock_guard<std::mutex> lock(_data_queue_mtx);
  DataContainer data_block;
  data_block.id = DataContainer::kInvalidId;
  if (_data_queue.empty()) {
    return data_block;
  }

  data_block = _data_queue.front();
  _data_queue.pop();

  return data_block;
}

std::size_t ResourceManagerImpl::get_last_block_id() {
  std::lock_guard<std::mutex> lock(_data_id_mtx);
  return _last_data_block_id;
}

}  // namespace resource_manager
