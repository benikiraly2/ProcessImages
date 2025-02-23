cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")
set(CMAKE_CXX_STANDARD 20)

project(APP)

find_package(Boost 1.85 REQUIRED COMPONENTS archive serialization)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

set(EXECUTABLE_NAME "APP")
add_executable(${EXECUTABLE_NAME} main.cpp)

target_link_libraries(
    ${EXECUTABLE_NAME}
    PRIVATE
        app::server
        -lsctp
)

add_subdirectory(app)

# find_package(GTest CONFIG REQUIRED)
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_subdirectory(tests)

# endif()
