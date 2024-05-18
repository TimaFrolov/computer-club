project(test-task)

add_subdirectory(Time)
add_subdirectory(Events)
add_subdirectory(Config)
add_subdirectory(Parser)
add_subdirectory(ComputerClub)
add_subdirectory(Simulator)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE simulator)
