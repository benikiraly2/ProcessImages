set(MODULE_NAME "sockets")

set(
    PUBLIC_HEADERS
        include/${MODULE_NAME}/Socket.hpp
)

set(
    INTERNAL_FILES
        src/Socket.cpp
)

add_library(${MODULE_NAME} ${INTERNAL_FILES} ${PUBLIC_HEADERS})
add_library(app::sockets ALIAS ${MODULE_NAME})

target_include_directories(
    ${MODULE_NAME}
    PUBLIC
        include
    PRIVATE
        src
)

target_link_libraries(
    ${MODULE_NAME}
    PRIVATE
        app::exceptions
)

