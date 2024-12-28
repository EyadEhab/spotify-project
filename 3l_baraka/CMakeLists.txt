cmake_minimum_required(VERSION 3.30)
project(3l_baraka)

set(CMAKE_CXX_STANDARD 14)

# Include directories
include_directories(src)

# Define source files
set(SOURCES
        src/main.cpp
        src/node.cpp
        src/playlist.cpp
        src/song.cpp
        src/BSTNode.cpp
        src/miniaudio.c
)

# Create miniaudio library
add_library(miniaudio STATIC src/miniaudio.c)
target_compile_definitions(miniaudio PRIVATE MINIAUDIO_IMPLEMENTATION)

if(UNIX)
    target_link_libraries(miniaudio PRIVATE
            m
            pthread
            dl
    )
endif()

# Create executable (only once!)
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against miniaudio and required system libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
        miniaudio
)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)