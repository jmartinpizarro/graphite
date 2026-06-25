cmake_minimum_required(VERSION 3.20)

project(graphite
    VERSION 1.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 

add_library(graphite INTERFACE)
add_library(graphite::graphite ALIAS graphite)

target_include_directories(graphite INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_precompile_headers(graphite INTERFACE
  <vector>
  <string>
  <unordered_map>
)

target_compile_options(graphite INTERFACE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -O2>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /O2>
)

target_compile_features(graphite INTERFACE cxx_std_23)

add_executable(graphite_app 
  src/main.cpp
)

target_link_libraries(graphite_app PRIVATE graphite::graphite)
