cmake_minimum_required(VERSION 3.5)
set (CMAKE_CXX_STANDARD 14)

project(fs_generator)

include(ExternalProject)

ExternalProject_Add(logger
    PREFIX ${CMAKE_BINARY_DIR}/logger
    GIT_REPOSITORY git@github.com:i-gap4uk/Logger.git
    GIT_TAG master
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/logger/build
    BUILD_BYPRODUCTS ${CMAKE_BINARY_DIR}/logger/build/liblogger.a
)

set(LOGGER_LIB ${CMAKE_BINARY_DIR}/logger/build/lib/liblogger.a)
set(LOGGER_INCLUDE_DIR ${CMAKE_BINARY_DIR}/logger/build/headers/)

include_directories(${CMAKE_SOURCE_DIR})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenSSL REQUIRED)

file(GLOB SOURCES "src/*.cpp" "utils/src/*.cpp")
file(GLOB HEADERS "utils/include/*.h" "include/*.h")

add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${LOGGER_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE ${LOGGER_LIB} OpenSSL::SSL pthread)

add_dependencies(${PROJECT_NAME} logger)
