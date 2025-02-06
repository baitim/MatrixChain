cmake_minimum_required(VERSION 3.11)
project(src)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)

find_package(Matrix REQUIRED)

add_executable(matrix_chain matrix_chain.cpp)
target_sources(matrix_chain
    PRIVATE
    FILE_SET HEADERS
    BASE_DIRS ${INCLUDE_DIR}
)
target_link_libraries(matrix_chain PRIVATE Matrix::Matrix)

add_library(MatrixChain matrix_chain.cpp)
target_include_directories(MatrixChain PUBLIC
    $<BUILD_INTERFACE:${INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(MatrixChain PRIVATE Matrix::Matrix)

install(TARGETS MatrixChain EXPORT MatrixChainTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY ${INCLUDE_DIR}/MatrixChain DESTINATION include)

install(EXPORT MatrixChainTargets
    FILE MatrixChainConfig.cmake
    DESTINATION lib/cmake/MatrixChain
)