set(MODULE_NAME_UT unitTests)

project(${MODULE_NAME_UT} LANGUAGES CXX)

set(
    SOURCES
        main.cpp
        TestClient.cpp
        TestExceptions.cpp
        TestServer.cpp
)

add_executable(
    ${MODULE_NAME_UT}
    ${SOURCES}
)


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
