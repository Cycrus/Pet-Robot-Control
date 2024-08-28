# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/build

# Include any dependencies generated for this target.
include CMakeFiles/graphics_test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/graphics_test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/graphics_test.dir/flags.make

CMakeFiles/graphics_test.dir/graphics_test.cpp.o: CMakeFiles/graphics_test.dir/flags.make
CMakeFiles/graphics_test.dir/graphics_test.cpp.o: ../graphics_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/graphics_test.dir/graphics_test.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/graphics_test.dir/graphics_test.cpp.o -c /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/graphics_test.cpp

CMakeFiles/graphics_test.dir/graphics_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/graphics_test.dir/graphics_test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/graphics_test.cpp > CMakeFiles/graphics_test.dir/graphics_test.cpp.i

CMakeFiles/graphics_test.dir/graphics_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/graphics_test.dir/graphics_test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/graphics_test.cpp -o CMakeFiles/graphics_test.dir/graphics_test.cpp.s

# Object files for target graphics_test
graphics_test_OBJECTS = \
"CMakeFiles/graphics_test.dir/graphics_test.cpp.o"

# External object files for target graphics_test
graphics_test_EXTERNAL_OBJECTS =

graphics_test: CMakeFiles/graphics_test.dir/graphics_test.cpp.o
graphics_test: CMakeFiles/graphics_test.dir/build.make
graphics_test: libInterfaceLibrary.a
graphics_test: ST7735_TFT_driver/libST7735_TFT_driver.so
graphics_test: keyboard_input/libkeyboard_input.so
graphics_test: CMakeFiles/graphics_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable graphics_test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/graphics_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/graphics_test.dir/build: graphics_test

.PHONY : CMakeFiles/graphics_test.dir/build

CMakeFiles/graphics_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/graphics_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/graphics_test.dir/clean

CMakeFiles/graphics_test.dir/depend:
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/build /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/build /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/face_controller/build/CMakeFiles/graphics_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/graphics_test.dir/depend
