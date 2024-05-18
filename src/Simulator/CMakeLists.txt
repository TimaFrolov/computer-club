project(simulator)

add_library(${PROJECT_NAME} STATIC Simulator.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE computer-club parser)
