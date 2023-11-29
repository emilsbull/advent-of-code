set(TARGET_NAME "advent22-10")


add_executable(${TARGET_NAME}
                main.cpp)

target_link_libraries(${TARGET_NAME}
PRIVATE
aoc_utils
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