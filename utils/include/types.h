#ifndef TYPES_H
#define TYPES_H

#include <limits>
#include <queue>
#include <string>

namespace common_types {
struct DataContainer {
  static constexpr std::size_t kInvalidId =
      std::numeric_limits<std::size_t>::max();

  explicit DataContainer(const std::size_t block_size = 0)
      : data(block_size, 0), id(kInvalidId) {}

  bool operator<(const DataContainer& other) const { return id < other.id; }

  void clear() {
    std::fill(data.begin(), data.end(), 0);
    id = 0;
  }

  bool is_valid() const { return (id != kInvalidId) && (data.size() > 0); }

  std::vector<char> data;
  std::size_t id;
};

using DataQueue = std::queue<DataContainer>;

struct HashContainer {
  static constexpr std::size_t kInvalidId =
      std::numeric_limits<std::size_t>::max();

  HashContainer() : id(kInvalidId) {}

  HashContainer(const std::string& source, std::size_t container_id)
      : hash(source), id(container_id) {}

  bool operator<(const HashContainer& other) const { return id < other.id; }

  bool is_valid() { return (id != kInvalidId) && (hash.size() > 0); }

  void clear() {
    hash.clear();
    id = 0;
  }

  std::string hash;
  std::size_t id;
};
using HashQueue = std::queue<HashContainer>;
}  // namespace common_types

#endif  // TYPES_H
