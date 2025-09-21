file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h")
add_library(NetworkLib ${SOURCES} ${INCLUDES})

target_include_directories(NetworkLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(NetworkLib PRIVATE SystemLib)
