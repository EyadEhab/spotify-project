cmake_minimum_required(VERSION 3.30)
project(3l_baraka)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(3l_baraka
    src/main.cpp
    src/node.cpp
    src/node.h
    src/playlist.cpp
    src/playlist.h
    src/song.cpp
    src/song.h)
