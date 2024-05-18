project(integration-tests)

add_definitions(-DTEST_DATA_PATH="${CMAKE_CURRENT_SOURCE_DIR}/data")

add_executable(${PROJECT_NAME} IntegrationTests.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main simulator)
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
