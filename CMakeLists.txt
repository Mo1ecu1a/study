cmake_minimum_required(VERSION 3.2...4.1)

project(study)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(menu)
add_subdirectory(src)

set(CMAKE_SUPPRESS_REGENERATION true)
