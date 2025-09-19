cmake_minimum_required(VERSION 3.16)
project(MultiplayerChat C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Ensure C++11 features are available
# if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wunused-parameter -Wunused-private-field")
# endif()

# add_subdirectory(thirdparty/SDL EXCLUDE_FROM_ALL)

include_directories(
	${CMAKE_SOURCE_DIR}/client/src,
    ${CMAKE_SOURCE_DIR}/server/src
)

# link_directories(
#     ${SDL3_LIBRARY_DIRS}
# )

file(GLOB CLIENT_SOURCES "client/src/*.c")
add_executable(${PROJECT_NAME}_Client ${CLIENT_SOURCES})
set_target_properties(${PROJECT_NAME}_Client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/client/build"
)

file(GLOB SERVER_SOURCES "server/src/*.c")
add_executable(${PROJECT_NAME}_Server ${SERVER_SOURCES})
set_target_properties(${PROJECT_NAME}_Server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/server/build"
)

# Add Unity testing framework
add_subdirectory(thirdparty/Unity EXCLUDE_FROM_ALL)

# Create test executables
add_executable(TestClient client/tests/src/main_test.c)
target_link_libraries(TestClient unity)
target_include_directories(TestClient PRIVATE thirdparty/Unity/src)

add_executable(TestServer server/tests/src/main_test.c)
target_link_libraries(TestServer unity)
target_include_directories(TestServer PRIVATE thirdparty/Unity/src)

# Enable testing
enable_testing()
add_test(NAME ClientTest COMMAND TestClient)
add_test(NAME ServerTest COMMAND TestServer)

# Add custom target to build and run tests automatically
add_custom_target(run-tests
    COMMENT "Building and running all tests"
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --verbose
    COMMAND echo "All tests passed!"
    DEPENDS TestClient TestServer
)

# Add custom target to build, test, and run the game if tests pass
add_custom_target(pre-run
    DEPENDS ${PROJECT_NAME}_Client ${PROJECT_NAME}_Server run-tests
)

# Add custom target to build, test, and run the game if tests pass
add_custom_target(run
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --verbose
    COMMAND echo "All tests passed! Starting game..."
    COMMAND $<TARGET_FILE:${PROJECT_NAME}_Client>
    DEPENDS ${PROJECT_NAME}_Client ${PROJECT_NAME}_Server TestClient TestServer
    COMMENT "Building game, running tests, and launching if tests pass"
)
