project(parser)

add_library(${PROJECT_NAME} STATIC Parser.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(
  ${PROJECT_NAME}
  PUBLIC events club-config
  PRIVATE time)
