cmake_minimum_required(VERSION 3.2)
project(parser C CXX)

set(SOURCE_FILES
    token.hpp
    scanner.hpp
    scanner.cpp
    expression.hpp
    expression.cpp
    parser.hpp
    parser.cpp
)

add_library(parser SHARED STATIC ${SOURCE_FILES})

install(TARGETS parser DESTINATION ${DIVISIBLE_INSTALL_LIB_DIR})
