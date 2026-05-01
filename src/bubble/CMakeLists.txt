#target_sources(${LIBRARY}
	#PRIVATE
	#	bubble.cpp
	#PUBLIC
		#bubble.hpp
#)

set(LIBRARY bubble)

add_library(${LIBRARY}
	bubble.cpp
	bubble.hpp
)

target_include_directories(${LIBRARY} PUBLIC
	"${PROJECT_SOURCE_DIR}/bubble"
)
