cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(member)

option(KEYS_BUILD_EXAMPLES "Build examples" OFF)

add_library(keys INTERFACE)
target_include_directories(
    keys 
    INTERFACE $<BUILD_INTERFACE: ${CMAKE_CURRENT_SOURCE_DIR}/include>
)

add_library(keys::all ALIAS keys)

if (KEYS_BUILD_EXAMPLES)
    message(STATUS "Building examples")
    add_executable(examples examples/main.cc)
    target_link_libraries(examples PUBLIC keys::all)
endif()

