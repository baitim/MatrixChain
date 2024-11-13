cmake_minimum_required(VERSION 3.11)
project(unit)

set(INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Matrix/include/
)

find_package(GTest REQUIRED)

add_executable(unit_matrix_chain matrix_chain_unit_test.cpp)
target_include_directories(unit_matrix_chain PUBLIC ${INCLUDE_DIR})
target_link_libraries(unit_matrix_chain gtest::gtest)

set(RUN_TESTS ./unit_matrix_chain --gtest_color=yes)
add_test(
    NAME unit_matrix_chain_target
    COMMAND ${RUN_TESTS}
)