cmake_minimum_required(VERSION 3.11)
project(src)

set(INCLUDE_DIR
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Matrix/include/
)

add_executable(matrix_chain matrix_chain.cpp)
target_include_directories(matrix_chain PUBLIC ${INCLUDE_DIR})

set(PYTHON_SCRIPT_RUN "${CMAKE_SOURCE_DIR}/tests/end_to_end/run_tests.py")
add_test(
    NAME run_matrix_target
    COMMAND bash -c "python3 ${PYTHON_SCRIPT_RUN}"
)