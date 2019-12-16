cmake_minimum_required(VERSION 3.0)
set (CMAKE_CXX_STANDARD 14)

project(file_signature_generator)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL REQUIRED)

file(GLOB SOURCES "src/*.cpp" "utils/src/*.cpp")
file(GLOB HEADERS "utils/include/*.h" "include/*.h")

add_executable(${PROJECT_NAME} src/main.cpp ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL pthread)
