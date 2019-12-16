#include "utils/include/hash_generator.h"

#include <openssl/evp.h>

#include <iomanip>
#include <iostream>
#include <sstream>

namespace hash_generator {

std::string hex_format(const unsigned char* hash_value,
                       const unsigned int hash_length) {
  std::stringstream sstream;

  for (std::size_t i = 0; i < hash_length; ++i) {
    sstream << std::hex << std::setw(2) << std::setfill('0')
            << static_cast<int>(hash_value[i]);
  }

  return sstream.str();
}

std::size_t HashGenerator::_hash_id{0};

HashGenerator::HashGenerator() {}

common_types::HashContainer HashGenerator::generate_hash(const Data& data) {
  if (data.empty()) {
    throw std::runtime_error("Data is empty. Hash generating aborted");
  }

  EVP_MD_CTX* ctx = EVP_MD_CTX_new();

  if (nullptr == ctx) {
    throw std::runtime_error("Error creating EVP_MD_CTX context");
  }

  EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr);
  if (EVP_DigestInit_ex(ctx, EVP_sha256(), nullptr) != 1) {
    throw std::runtime_error("EVP_DigestInit_ex is failed!");
  }

  if (EVP_DigestUpdate(ctx, data.data(), data.size()) != 1) {
    throw std::runtime_error("DigestUpdate is failed!");
  }

  unsigned char buffer[EVP_MAX_MD_SIZE];
  unsigned int hash_length;

  if (EVP_DigestFinal_ex(ctx, buffer, &hash_length) != 1) {
    throw std::runtime_error("DigestFinal is failed!");
  }

  EVP_MD_CTX_free(ctx);

  common_types::HashContainer hash;
  hash.hash = hex_format(buffer, hash_length);
  hash.id = ++_hash_id;

  return hash;
}

}  // namespace hash_generator
