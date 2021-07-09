cmake_minimum_required (VERSION 3.1.3)

## Project
project (JsonTestExample CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

## Build
add_executable (${PROJECT_NAME} "")

## Version
include(version)

## Sources
target_sources(
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

## Headers
target_include_directories (
    ${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/nlohmann
)

# Link external/3rd party libs
target_link_libraries (
    ${PROJECT_NAME}
    PRIVATE
)

# Compilation Params
# Note: for compiling againts JSON header, c++11 std is necessary
target_compile_options (
    ${PROJECT_NAME}
    PRIVATE
        -std=c++11
        -Wall
        -Werror
        -Wunused
        -pedantic
)

# Custom Commands

# Installation Lib/Binary/Systemd Service/DBus Service Config
install (
    TARGETS         ${TARGET}
    DESTINATION     ${PROJECT_SOURCE_DIR}/build
)
