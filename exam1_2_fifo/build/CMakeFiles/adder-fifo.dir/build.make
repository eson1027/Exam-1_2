# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/user/ee6470/exam/exam1_2_fifo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/user/ee6470/exam/exam1_2_fifo/build

# Include any dependencies generated for this target.
include CMakeFiles/adder-fifo.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/adder-fifo.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/adder-fifo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/adder-fifo.dir/flags.make

CMakeFiles/adder-fifo.dir/main.cpp.o: CMakeFiles/adder-fifo.dir/flags.make
CMakeFiles/adder-fifo.dir/main.cpp.o: ../main.cpp
CMakeFiles/adder-fifo.dir/main.cpp.o: CMakeFiles/adder-fifo.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/user/ee6470/exam/exam1_2_fifo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/adder-fifo.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/adder-fifo.dir/main.cpp.o -MF CMakeFiles/adder-fifo.dir/main.cpp.o.d -o CMakeFiles/adder-fifo.dir/main.cpp.o -c /home/user/ee6470/exam/exam1_2_fifo/main.cpp

CMakeFiles/adder-fifo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/adder-fifo.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/user/ee6470/exam/exam1_2_fifo/main.cpp > CMakeFiles/adder-fifo.dir/main.cpp.i

CMakeFiles/adder-fifo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/adder-fifo.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/user/ee6470/exam/exam1_2_fifo/main.cpp -o CMakeFiles/adder-fifo.dir/main.cpp.s

# Object files for target adder-fifo
adder__fifo_OBJECTS = \
"CMakeFiles/adder-fifo.dir/main.cpp.o"

# External object files for target adder-fifo
adder__fifo_EXTERNAL_OBJECTS =

adder-fifo: CMakeFiles/adder-fifo.dir/main.cpp.o
adder-fifo: CMakeFiles/adder-fifo.dir/build.make
adder-fifo: CMakeFiles/adder-fifo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/user/ee6470/exam/exam1_2_fifo/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable adder-fifo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/adder-fifo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/adder-fifo.dir/build: adder-fifo
.PHONY : CMakeFiles/adder-fifo.dir/build

CMakeFiles/adder-fifo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/adder-fifo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/adder-fifo.dir/clean

CMakeFiles/adder-fifo.dir/depend:
	cd /home/user/ee6470/exam/exam1_2_fifo/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/user/ee6470/exam/exam1_2_fifo /home/user/ee6470/exam/exam1_2_fifo /home/user/ee6470/exam/exam1_2_fifo/build /home/user/ee6470/exam/exam1_2_fifo/build /home/user/ee6470/exam/exam1_2_fifo/build/CMakeFiles/adder-fifo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/adder-fifo.dir/depend

