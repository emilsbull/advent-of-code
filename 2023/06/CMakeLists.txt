set(TARGET_NAME "advent23-06")


add_executable(${TARGET_NAME}
                main.cpp)

target_link_libraries(${TARGET_NAME}
PUBLIC
    aoc_utils
PRIVATE
    stdc++fs)

target_compile_options(${TARGET_NAME}
PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
