file(GLOB CLIENT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
add_executable(${PROJECT_NAME}_Client ${CLIENT_SOURCES})
set_target_properties(${PROJECT_NAME}_Client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

# Add Test Executable
add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME}_Client PRIVATE NetworkLib)