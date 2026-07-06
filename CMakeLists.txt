cmake_minimum_required(VERSION 3.21) 

project(graphite
    VERSION 1.2.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# lib definition
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

# binary for execution
add_executable(graphite_app 
  src/main.cpp
)

target_link_libraries(graphite_app PRIVATE graphite::graphite)


option(GRAPHITE_BUILD_TESTS "Builds tests for graphite" ${PROJECT_IS_TOP_LEVEL})

if (GRAPHITE_BUILD_TESTS)
  # build with GoogleTest for testing the project 
  include(FetchContent)
  cmake_policy(SET CMP0135 NEW)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  FetchContent_MakeAvailable(googletest)

  enable_testing()

  # binary for tests??
  add_executable(test_graph
  tests/test_graph.cpp
  )

  target_link_libraries(
  test_graph
  GTest::gtest
  GTest::gtest_main
  graphite::graphite
  )

  include(GoogleTest)
  gtest_discover_tests(test_graph)
endif()
