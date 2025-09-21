cmake_minimum_required(VERSION 3.16)
project(MultiplayerChat C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(thirdparty/Unity)
add_subdirectory(lib/system)
add_subdirectory(lib/network)

# Client
add_subdirectory(client)

# Server
add_subdirectory(server)

# Testing
enable_testing()
add_test(NAME ClientTest COMMAND ${PROJECT_NAME}_TestClient)
add_test(NAME ServerTest COMMAND ${PROJECT_NAME}_TestServer)

# Add custom target to build and run tests automatically
add_custom_target(run-tests
    COMMENT "Building and running all tests"
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure --verbose
    COMMAND echo "All tests passed!"
    DEPENDS ${PROJECT_NAME}_TestClient ${PROJECT_NAME}_TestServer
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
    DEPENDS ${PROJECT_NAME}_Client ${PROJECT_NAME}_Server ${PROJECT_NAME}_TestClient ${PROJECT_NAME}_TestServer
    COMMENT "Building game, running tests, and launching if tests pass"
)
