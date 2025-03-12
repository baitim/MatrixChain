cmake_minimum_required(VERSION 3.30)
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

if(DEFINED ENV{CONAN_PACKAGE})
    include(GNUInstallDirs)

    add_library(MatrixChain matrix_chain.cpp)
    target_include_directories(MatrixChain PUBLIC
        $<BUILD_INTERFACE:${INCLUDE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    )
    target_link_libraries(MatrixChain PRIVATE Matrix::Matrix)

    install(TARGETS MatrixChain EXPORT MatrixChainTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    install(DIRECTORY ${INCLUDE_DIR}/MatrixChain DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    install(EXPORT MatrixChainTargets
        FILE MatrixChainConfig.cmake
        DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/MatrixChain
    )
endif()