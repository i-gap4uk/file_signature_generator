#ifndef UTILS_CONSTANTS_H
#define UTILS_CONSTANTS_H

#include <string>

namespace common_constants {

constexpr const char* kDefaultSignatureFilePath = "file_signature.txt";
const std::size_t kDefaultBlockSize = 1;  // 1Mb
const std::size_t kDefaultThreadsAmount = 1;
const std::size_t kBytesInMb = 1048576;
const std::size_t kMinReasonableThreadsAmount = 4;

enum InputParameters { INPUT_FILE = 1, SIGNATURE_FILE, BLOCK_SIZE };
enum READING_RESULT { INVALID = -1, COMPLETED, END_OF_FILE };
}  // namespace common_constants

namespace log_constants {

enum class LogLevel { INFO = 0, DEBUG, WARNING, ERROR };
enum class LogDestination { CONSOLE = 0, FILE };

#define INFO log_constants::LogLevel::INFO
#define DEBUG log_constants::LogLevel::DEBUG
#define WARNING log_constants::LogLevel::WARNING
#define ERROR log_constants::LogLevel::ERROR

constexpr const char* default_logfile_name = "fsg_logfile.log";

}  // namespace log_constants

#endif  // UTILS_CONSTANTS_H
