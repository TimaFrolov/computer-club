cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

project(
  test-task
  VERSION 0.1.0
  LANGUAGES CXX)

add_subdirectory(src)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  add_subdirectory(tests)
endif()
