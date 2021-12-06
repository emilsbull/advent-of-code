set(TARGET_NAME "advent05b")
add_executable(${TARGET_NAME}
                main.cpp)

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

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input1.txt
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})