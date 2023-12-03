set(MODULE_NAME_UT unitTests)

project(${MODULE_NAME_UT} LANGUAGES CXX)

set(
    SOURCES
        main.cpp
        TestClient.cpp
)

add_executable(
    ${MODULE_NAME_UT}
    ${SOURCES}
)

# add_executable(example example.cpp)

# target_link_libraries(${MODULE_NAME_UT} gtest_main)

target_link_libraries(
    ${MODULE_NAME_UT}
    PRIVATE
        app::clients
        app::exceptions
        app::sockets
        app::server
        app::workers
        gtest_main
)

add_test(NAME ${MODULE_NAME_UT} COMMAND ${MODULE_NAME_UT})

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# include(GoogleTest)
# gtest_discover_tests(${MODULE_NAME_UT})
