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
CMAKE_SOURCE_DIR = /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build

# Include any dependencies generated for this target.
include ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/depend.make

# Include the progress variables for this target.
include ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/progress.make

# Include the compile flags for this target's objects.
include ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/flags.make

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.o: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/flags.make
ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.o: /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.o"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.o -c /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT.cpp

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.i"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT.cpp > CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.i

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.s"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT.cpp -o CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.s

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.o: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/flags.make
ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.o: /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT_Print.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.o"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.o -c /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT_Print.cpp

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.i"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT_Print.cpp > CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.i

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.s"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT_Print.cpp -o CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.s

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.o: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/flags.make
ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.o: /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT_graphics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.o"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.o -c /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT_graphics.cpp

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.i"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT_graphics.cpp > CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.i

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.s"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_TFT_graphics.cpp -o CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.s

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.o: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/flags.make
ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.o: /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_Utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.o"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.o -c /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_Utils.cpp

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.i"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_Utils.cpp > CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.i

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.s"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver/src/ST7735_Utils.cpp -o CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.s

# Object files for target ST7735_TFT_driver
ST7735_TFT_driver_OBJECTS = \
"CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.o" \
"CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.o" \
"CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.o" \
"CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.o"

# External object files for target ST7735_TFT_driver
ST7735_TFT_driver_EXTERNAL_OBJECTS =

ST7735_TFT_driver/libST7735_TFT_driver.so: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT.cpp.o
ST7735_TFT_driver/libST7735_TFT_driver.so: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_Print.cpp.o
ST7735_TFT_driver/libST7735_TFT_driver.so: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_TFT_graphics.cpp.o
ST7735_TFT_driver/libST7735_TFT_driver.so: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/src/ST7735_Utils.cpp.o
ST7735_TFT_driver/libST7735_TFT_driver.so: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/build.make
ST7735_TFT_driver/libST7735_TFT_driver.so: ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library libST7735_TFT_driver.so"
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ST7735_TFT_driver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/build: ST7735_TFT_driver/libST7735_TFT_driver.so

.PHONY : ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/build

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/clean:
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver && $(CMAKE_COMMAND) -P CMakeFiles/ST7735_TFT_driver.dir/cmake_clean.cmake
.PHONY : ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/clean

ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/depend:
	cd /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/lib/c++/ST7735_TFT_driver /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver /home/cycrus/Documents/Pet-Robot-Control/RaspberryPi/interfaces/c++/helloworld/build/ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ST7735_TFT_driver/CMakeFiles/ST7735_TFT_driver.dir/depend

