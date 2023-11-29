set(MODULE_NAME "workers")

set(
    PUBLIC_HEADERS
        include/${MODULE_NAME}/Worker.hpp
)

set(
    INTERNAL_FILES
        src/Worker.cpp
)

add_library(${MODULE_NAME} ${INTERNAL_FILES} ${PUBLIC_HEADERS})
add_library(app::workers ALIAS ${MODULE_NAME})

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
        app::clients
)

