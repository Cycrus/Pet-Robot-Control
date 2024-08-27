cmake_minimum_required(VERSION 3.18.4)

# Library name (use the directory name as the project name)
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${LIBRARY_NAME})

# Specify the directories containing headers for this library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Gather all the source files in src/
file(GLOB LIBRARY_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# Create a shared library
add_library(${LIBRARY_NAME} SHARED ${LIBRARY_SOURCES})
