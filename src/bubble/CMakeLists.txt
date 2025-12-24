target_sources(${LIBRARY}
	PRIVATE
		bubble.cpp
	PUBLIC
		bubble.hpp
)

target_include_directories(${LIBRARY} PUBLIC
	"${PROJECT_SOURCE_DIR}/src"
)
