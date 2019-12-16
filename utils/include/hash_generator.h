#ifndef HASH_GENERATOR_H
#define HASH_GENERATOR_H

#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "utils/include/types.h"

namespace hash_generator {

using Data = std::vector<char>;

class HashGenerator {
 public:
  HashGenerator();

  common_types::HashContainer generate_hash(const Data& data);

 private:
  static std::size_t _hash_id;
};

using HashGeneratorPtr = std::shared_ptr<HashGenerator>;

}  // namespace hash_generator

#endif  // HASH_GENERATOR_H
