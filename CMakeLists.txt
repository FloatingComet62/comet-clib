cmake_minimum_required(VERSION 3.0.0)
project(lib VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

list(APPEND sources
  ${CMAKE_CURRENT_LIST_DIR}/main.c
)

include(lib/CMakeLists.txt)
add_executable(lib ${sources})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
