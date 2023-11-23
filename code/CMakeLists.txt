cmake_minimum_required(VERSION 3.17)
project(Batalla_Naval VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(Batalla_Naval main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
