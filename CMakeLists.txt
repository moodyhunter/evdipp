cmake_minimum_required(VERSION 3.22.0)
project(evdipp)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(evdi)

add_subdirectory(libevdipp)
add_subdirectory(example)
add_subdirectory(monitorsim)
