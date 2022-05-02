cmake_minimum_required(VERSION 3.22)

project(infosec_labs VERSION 1.2)

set(CMAKE_CXX_STANDARD 20)
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_BINARY_DIR})

configure_file(config.h.in config.h)

add_subdirectory(program_options)
add_subdirectory(cyphers)
add_subdirectory(encryptor)
