project(tests)

set(LIBRARY
	lib
)

add_library(${LIBRARY} "")

add_subdirectory(bubble)
add_subdirectory(test)
