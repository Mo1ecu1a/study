cmake_minimum_required(VERSION 3.10)
project(long_number)

set(LIBRARY LN_lib)

add_library(${LIBRARY})

add_subdirectory(src)
add_subdirectory(tests)
