file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/includes/*.h")
add_library(SystemLib ${SOURCES} ${INCLUDES})

target_include_directories(SystemLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
