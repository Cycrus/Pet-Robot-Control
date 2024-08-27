cmake_minimum_required(VERSION 3.18.4)

project(Interface)

# Add external static dependencies
file(GLOB LIBRARY_DIRS "${CMAKE_SOURCE_DIR}/../../../lib/c++/*")
foreach(LIB_DIR ${LIBRARY_DIRS})
  if(IS_DIRECTORY ${LIB_DIR})
    # Specify the binary directory explicitly
    get_filename_component(LIB_NAME ${LIB_DIR} NAME)
    add_subdirectory(${LIB_DIR} ${CMAKE_BINARY_DIR}/${LIB_NAME})
    # Include the library's headers in the main project
    include_directories(${LIB_DIR}/inc)
  
    # Store the library target name
    list(APPEND LIBRARY_TARGETS ${LIB_NAME})
  endif()
endforeach()

set(LIBRARY_TARGETS "")
foreach(LIB_DIR ${LIBRARY_DIRS})
    get_filename_component(LIB_NAME ${LIB_DIR} NAME)
    list(APPEND LIBRARY_TARGETS ${LIB_NAME})
endforeach()

# Add internal static dependencies
if(EXISTS "${CMAKE_SOURCE_DIR}/inc")
  include_directories(${CMAKE_SOURCE_DIR}/inc)
endif()

if(EXISTS "${CMAKE_SOURCE_DIR}/src")
  file(GLOB SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
  add_library(InterfaceLibrary STATIC ${SRC_FILES})
endif()

file(GLOB MAIN_FILES ${CMAKE_SOURCE_DIR}/*.cpp)

# Handle every .cpp file in the root of the interface as an executable.
foreach(MAIN_FILE ${MAIN_FILES})
    get_filename_component(EXECUTABLE_NAME ${MAIN_FILE} NAME_WE)
    add_executable(${EXECUTABLE_NAME} ${MAIN_FILE})
    
    if(TARGET InterfaceLibrary)
      target_link_libraries(${EXECUTABLE_NAME} InterfaceLibrary)
    endif()

    target_link_libraries(${EXECUTABLE_NAME} ${LIBRARY_TARGETS})
endforeach()
