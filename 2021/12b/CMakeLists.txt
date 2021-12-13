set(TARGET_NAME "advent12b")


add_executable(${TARGET_NAME}
                main.cpp)

target_include_directories(${TARGET_NAME}
PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../../utils
)

target_link_libraries(${TARGET_NAME}
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