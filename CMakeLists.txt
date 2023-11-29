cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_CXX_STANDARD 20)

project(APP)

set(EXECUTABLE_NAME "APP")
add_executable(${EXECUTABLE_NAME} main.cpp)

target_link_libraries(
    ${EXECUTABLE_NAME}
    PRIVATE
        app::server
)

add_subdirectory(app)