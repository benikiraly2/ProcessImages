set(MODULE_NAME "server")

set(
    PUBLIC_HEADERS
        include/${MODULE_NAME}/Server.hpp
        include/${MODULE_NAME}/ServerWrapper.hpp
        include/${MODULE_NAME}/Timer.hpp
)

set(
    INTERNAL_FILES
        # src/Messages.hpp
        src/Server.cpp
        src/ServerWrapper.cpp
        src/Timer.cpp
)

add_library(${MODULE_NAME} ${INTERNAL_FILES} ${PUBLIC_HEADERS})
add_library(app::server ALIAS ${MODULE_NAME})

target_include_directories(
    ${MODULE_NAME}
    PUBLIC
        include
    PRIVATE
        src
)

target_link_libraries(
    ${MODULE_NAME}
    PUBLIC
        app::sockets
        app::clients
        app::workers
    PRIVATE
        app::exceptions
)
