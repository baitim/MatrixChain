cmake_minimum_required(VERSION 3.11)
project(compare)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

find_package(Matrix REQUIRED)

add_executable(cmp_matrix_chain matrix_chain_cmp.cpp)
target_sources(cmp_matrix_chain
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)
target_link_libraries(cmp_matrix_chain Matrix::Matrix)