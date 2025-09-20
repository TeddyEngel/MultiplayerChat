file(GLOB CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME}_Server ${CLIENT_SOURCES})
set_target_properties(${PROJECT_NAME}_Server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

# Add Test Executable
add_subdirectory(tests)