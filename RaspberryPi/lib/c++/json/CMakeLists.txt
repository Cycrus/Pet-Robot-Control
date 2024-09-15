cmake_minimum_required(VERSION 3.18.4)

# Library name (use the directory name as the project name)
get_filename_component(LIBRARY_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${LIBRARY_NAME})

# Specify the directories containing headers for this library
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Create a shared library
add_library(${LIBRARY_NAME} INTERFACE)

# Specify the include directories for this library target
target_include_directories(${LIBRARY_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
