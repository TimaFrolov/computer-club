project(time)

add_library(${PROJECT_NAME} STATIC Time.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
