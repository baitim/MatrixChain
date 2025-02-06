cmake_minimum_required(VERSION 3.11)
project(unit)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

find_package(GTest REQUIRED)
find_package(Matrix REQUIRED)

add_executable(unit_matrix_chain matrix_chain_unit_test.cpp)
target_sources(unit_matrix_chain
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)
target_link_libraries(unit_matrix_chain PRIVATE gtest::gtest Matrix::Matrix)

set(RUN_TESTS ./unit_matrix_chain --gtest_color=yes)
add_test(
    NAME unit_matrix_chain_target
    COMMAND ${RUN_TESTS}
)