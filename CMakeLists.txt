cmake_minimum_required(VERSION 3.5.0)
project(proj VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set (CMAKE_CXX_STANDARD 23)

add_executable(proj main.cpp img.cpp command.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
