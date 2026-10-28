#[[
RoseAPI - A modding API for Sub Rosa.
Copyright (C) 2026 swagtib
 
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.
 
You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
]]

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

find_path(TCC_INCLUDE_DIR libtcc.h HINTS "/usr/local/include" REQUIRED)
find_library(TCC_LIBRARY NAMES tcc HINTS "/usr/local/lib" REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LibEdit REQUIRED IMPORTED_TARGET libedit)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_C_FLAGS_DEBUG   "-O0 -g3 -ggdb3")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_SOURCE_DIR}/src/*.c")

add_library(RoseAPI SHARED ${SOURCES})

include(CheckIPOSupported)
check_ipo_supported(RESULT ipostatus OUTPUT ipoerror)
if (ipostatus)
    set_property(TARGET RoseAPI PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
    message(WARNING "ipo isn't supported ${ipoerror}")
endif()

target_include_directories(RoseAPI
    PUBLIC  "${CMAKE_SOURCE_DIR}/src" "${CMAKE_SOURCE_DIR}/public"
    PRIVATE "${FRIDA_GUM_DEVKIT_DIR}" "${TCC_INCLUDE_DIR}"
)

target_link_libraries(RoseAPI PRIVATE
    "${FRIDA_GUM_DEVKIT_DIR}/libfrida-gum.a"
    "${TCC_LIBRARY}"
    PkgConfig::LibEdit
    dl m rt pthread
)

target_link_options(RoseAPI PRIVATE
    -Wl,--exclude-libs,ALL
    -Wl,--gc-sections
)

set_target_properties(RoseAPI PROPERTIES
    C_VISIBILITY_PRESET hidden
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)