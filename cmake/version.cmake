find_program(BASH NAMES bash)

execute_process(
    COMMAND ${BASH} -c "git describe --tags --always --dirty"
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_STRIP_TRAILING_WHITESPACE
    OUTPUT_VARIABLE APP_GIT_VERSION
)

if(APP_GIT_VERSION)
    add_definitions(-DAPP_VERSION="${APP_GIT_VERSION}")
    message(STATUS "Using MyApp version " ${APP_GIT_VERSION})
endif()