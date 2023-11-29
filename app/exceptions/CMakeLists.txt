set(MODULE_NAME "exceptions")

set(
    PUBLIC_HEADERS
        include/${MODULE_NAME}/Exceptions.hpp
)

set(
    INTERNAL_FILES
        src/Exceptions.cpp
)

add_library(${MODULE_NAME} ${INTERNAL_FILES} ${PUBLIC_HEADERS})
add_library(app::exceptions ALIAS ${MODULE_NAME})

target_include_directories(
    ${MODULE_NAME}
    PUBLIC
        include
    PRIVATE
        src
)
