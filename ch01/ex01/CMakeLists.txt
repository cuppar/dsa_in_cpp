cmake_minimum_required(VERSION 3.6)

project(example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# add utils
add_library(timer)
target_sources(
  timer
  PUBLIC ../../util/timer.h
  PRIVATE ../../util/timer.cpp)

# add exec
add_executable(main main.cpp)

# link
target_link_libraries(main PRIVATE timer)
