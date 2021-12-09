set(TARGET_NAME "advent08")


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
    $<$<BOOL:${USING_BS3}>:-Wconversion>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-error=unused-command-line-argument>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-error=dollar-in-identifier-extension>
    $<$<CXX_COMPILER_ID:Clang>:-Wno-error=macro-redefined>
)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/input1.txt ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)