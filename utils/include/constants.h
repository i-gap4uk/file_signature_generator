#ifndef UTILS_CONSTANTS_H
#define UTILS_CONSTANTS_H

#include <string>

namespace common_constants {

constexpr const char* kDefaultSignatureFilePath = "file_signature.txt";
const std::size_t kDefaultBlockSize = 1;  // 1Mb
const std::size_t kDefaultThreadsAmount = 1;
const std::size_t kBytesInMb = 1048576;
const std::size_t kMinReasonableThreadsAmount = 4;
constexpr const char* kInputFileArgumentKey = "-i";
constexpr const char* kOutputFileArgumentKey = "-o";
constexpr const char* kBlockSizeArgumentKey = "-bs";

enum READING_RESULT { INVALID = -1, COMPLETED, END_OF_FILE };
}  // namespace common_constants

#endif  // UTILS_CONSTANTS_H
