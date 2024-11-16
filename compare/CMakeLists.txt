cmake_minimum_required(VERSION 3.11)
project(compare)

set(INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Matrix/include/
)
add_executable(cmp_matrix_chain matrix_chain_cmp.cpp)
target_include_directories(cmp_matrix_chain PUBLIC ${INCLUDE_DIR})