cmake_policy(SET CMP0003 NEW)

link_directories(/usr/lib/x86_64-linux-gnu)
include_directories(/usr/src/googletest/googletest/include)

add_executable(long_number_test
    ${CMAKE_CURRENT_SOURCE_DIR}/long_number_test.cpp
)

target_link_libraries(long_number_test
    ${LIBRARY}
    gtest
    gtest_main
    pthread
)

target_include_directories(long_number_test PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)

add_test(NAME long_number_test COMMAND long_number_test)
