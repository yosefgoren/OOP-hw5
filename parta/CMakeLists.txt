cmake_minimum_required(VERSION 3.0.0)
project(lisp VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(given_test part1_test.cpp)
add_executable(test_parta test_parta.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
