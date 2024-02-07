cmake_minimum_required(VERSION 3.0.0)
project(lib VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

list(APPEND sources
  ${CMAKE_CURRENT_LIST_DIR}/string.c
  ${CMAKE_CURRENT_LIST_DIR}/log.c
  ${CMAKE_CURRENT_LIST_DIR}/optionals.c
  ${CMAKE_CURRENT_LIST_DIR}/vec.c
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
