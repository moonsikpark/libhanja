# Copyright (c) 2022 ESTsoft Corp. All rights reserved.

cmake_minimum_required(VERSION 3.19)

PROJECT(libhanja
        VERSION 0.1
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories("include")
include_directories("dependencies")

IF (WIN32)
        find_package(pybind11 CONFIG REQUIRED)
        find_package(Python3 REQUIRED)
ELSE()
        add_subdirectory("dependencies/pybind11")
ENDIF()

set(SOURCES
	src/convert.cc
        src/types.cc
        src/dictionary.cc
)

add_executable(hanja src/main.cc ${SOURCES})

pybind11_add_module(pyhanja src/pyhanja.cc ${SOURCES})

target_compile_definitions(pyhanja
                           PRIVATE VERSION_INFO=${EXAMPLE_VERSION_INFO})
