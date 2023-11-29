set(MODULE_NAME "clients")

set(
    PUBLIC_HEADERS
        include/${MODULE_NAME}/Client.hpp
)

set(
    INTERNAL_FILES
        src/Client.cpp
)

add_library(${MODULE_NAME} ${INTERNAL_FILES} ${PUBLIC_HEADERS})
add_library(app::clients ALIAS ${MODULE_NAME})

target_include_directories(
    ${MODULE_NAME}
    PUBLIC
        include
    PRIVATE
        src
)
