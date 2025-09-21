file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h")
add_executable(${PROJECT_NAME}_Server ${SOURCES} ${INCLUDES})
set_target_properties(${PROJECT_NAME}_Server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)

target_include_directories(${PROJECT_NAME}_Server PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

# Add Test Executable
add_subdirectory(tests)

target_link_libraries(${PROJECT_NAME}_Server 
                        PRIVATE SystemLib
                        PRIVATE NetworkLib)