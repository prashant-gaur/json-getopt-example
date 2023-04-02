cmake_minimum_required (VERSION 3.1.3)

## Project
project (nlohmann-json-parser-examples)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Build
add_executable (${PROJECT_NAME} "")

# Version
include(version)

# Source
target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc)

# Headers
target_include_directories (${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/nlohmann)

# Link external/3rd party libs
target_link_libraries (${PROJECT_NAME} PRIVATE)

# Compiler flags and options
target_compile_options (${PROJECT_NAME} PRIVATE -std=c++11 -Wall -Werror -Wunused -pedantic)

# Define macros for the source
add_definitions(-DAPP_NAME="${PROJECT_NAME}")

# Custom Commands

# Installation Lib/Binary/Systemd Service/DBus Service Config
install (
    TARGETS         ${TARGET}
    DESTINATION     ${PROJECT_SOURCE_DIR}/build
)
