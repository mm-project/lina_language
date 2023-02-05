cmake_minimum_required(VERSION 3.21)
project(main)

add_subdirectory(parser)
set(SOURCE_FILES main.cpp)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main parser)
install(TARGETS main DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})
