cmake_minimum_required(VERSION 3.12)
project(RoseAPI C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_SYSTEM_NAME STREQUAL "Linux")
    message(FATAL_ERROR "unsupported OS")
endif()

set(FRIDA_GUM_DEVKIT_DIR "" CACHE PATH "dir containing frida-gum.h and libfrida-gum.a")

if(NOT FRIDA_GUM_DEVKIT_DIR)
    message(FATAL_ERROR "set FRIDA_GUM_DEVKIT_DIR")
endif()
if(NOT EXISTS "${FRIDA_GUM_DEVKIT_DIR}/frida-gum.h" OR NOT EXISTS "${FRIDA_GUM_DEVKIT_DIR}/libfrida-gum.a")
    message(FATAL_ERROR "frida-gum.h / libfrida-gum.a not found")
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_C_FLAGS_DEBUG   "-O0 -g3 -ggdb3")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c")

add_library(RoseAPI SHARED ${SOURCES})

target_include_directories(RoseAPI
    PUBLIC  "${CMAKE_SOURCE_DIR}/src"
    PRIVATE "${FRIDA_GUM_DEVKIT_DIR}"
)

target_link_libraries(RoseAPI PRIVATE
    "${FRIDA_GUM_DEVKIT_DIR}/libfrida-gum.a"
    dl m rt pthread
)

target_link_options(RoseAPI PRIVATE
    -Wl,--exclude-libs,ALL
    -Wl,--gc-sections
)

set_target_properties(RoseAPI PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)