set(SOURCES 
	test_bubble.cpp
)

add_executable(test_bubble ${SOURCES})

target_link_libraries(test_bubble 
	#${LIBRARY}
	bubble
	gtest
	gtest_main 
)

add_test(NAME test_bubble COMMAND test_bubble)
