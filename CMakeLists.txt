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

set(SOURCES
	src/hanja.cc
        src/dictionary.cc
)

add_executable(hanja src/main.cc ${SOURCES})
