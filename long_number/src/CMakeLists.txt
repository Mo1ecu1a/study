target_sources(${LIBRARY}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/long_number.cpp
)

target_include_directories(${LIBRARY} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
