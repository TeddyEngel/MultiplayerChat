add_executable(${PROJECT_NAME}_TestServer ${CMAKE_CURRENT_SOURCE_DIR}/src/main_test.c)
set_target_properties(${PROJECT_NAME}_TestServer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

target_include_directories(${PROJECT_NAME}_TestServer INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}_TestServer PRIVATE unity)