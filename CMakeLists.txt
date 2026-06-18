cmake_minimum_required(VERSION 3.20)

project(graphite
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# graph lib
add_library(graph INTERFACE)
add_library(graph::graph ALIAS graph)

target_include_directories(graph INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(graph INTERFACE cxx_std_23)

# algorithm library - dependant on graph
add_library(algorithms INTERFACE)
add_library(algorithms::algorithms ALIAS algorithms)

target_include_directories(algorithms INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(algorithms INTERFACE cxx_std_23)

# a library utils has been also implemented
add_library(utils INTERFACE)
add_library(utils::utils ALIAS utils)

target_include_directories(utils INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_compile_features(utils INTERFACE cxx_std_23)


# define dependency on graph library
target_link_libraries(algorithms INTERFACE graph::graph)


add_executable(graphite_app 
  src/main.cpp
)

target_link_libraries(graphite_app
  PRIVATE
    graph::graph
    algorithms::algorithms
    utils::utils
)



