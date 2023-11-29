source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR})

set(TARGET_NAME aoc_utils)

add_library(${TARGET_NAME} INTERFACE
)

target_include_directories(${TARGET_NAME}
INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

target_compile_options(${TARGET_NAME}
INTERFACE
    -std=c++17 # armclang 6.6 supports officially c++11 (supports C++14 as a community feature)
)

install(
TARGETS ${TARGET_NAME}
COMPONENT TARGET_COMPONENT
DESTINATION lib
INCLUDES DESTINATION include/${PROJECT_NAME}
)

install(
DIRECTORY externInterface/
COMPONENT TARGET_COMPONENT
DESTINATION include/${PROJECT_NAME}
FILES_MATCHING PATTERN "*.h"
)