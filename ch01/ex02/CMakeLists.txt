cmake_minimum_required(VERSION 3.6)

project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
cmake_policy(SET CMP0076 NEW)

# add utils
add_library(util)
target_sources(
  util
  PUBLIC ../../util/Timer.h ../../util/Random.h
  PRIVATE ../../util/Timer.cpp)
target_include_directories(util PUBLIC ../../util)

# add exec
add_executable(main main.cpp)

# link
target_link_libraries(main PRIVATE util)
