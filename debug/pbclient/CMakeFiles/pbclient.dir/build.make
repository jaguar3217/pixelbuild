# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/luchiz/pixelbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/luchiz/pixelbuild/debug

# Include any dependencies generated for this target.
include pbclient/CMakeFiles/pbclient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include pbclient/CMakeFiles/pbclient.dir/compiler_depend.make

# Include the progress variables for this target.
include pbclient/CMakeFiles/pbclient.dir/progress.make

# Include the compile flags for this target's objects.
include pbclient/CMakeFiles/pbclient.dir/flags.make

pbclient/CMakeFiles/pbclient.dir/main.cpp.o: pbclient/CMakeFiles/pbclient.dir/flags.make
pbclient/CMakeFiles/pbclient.dir/main.cpp.o: /home/luchiz/pixelbuild/pbclient/main.cpp
pbclient/CMakeFiles/pbclient.dir/main.cpp.o: pbclient/CMakeFiles/pbclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/luchiz/pixelbuild/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object pbclient/CMakeFiles/pbclient.dir/main.cpp.o"
	cd /home/luchiz/pixelbuild/debug/pbclient && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT pbclient/CMakeFiles/pbclient.dir/main.cpp.o -MF CMakeFiles/pbclient.dir/main.cpp.o.d -o CMakeFiles/pbclient.dir/main.cpp.o -c /home/luchiz/pixelbuild/pbclient/main.cpp

pbclient/CMakeFiles/pbclient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/pbclient.dir/main.cpp.i"
	cd /home/luchiz/pixelbuild/debug/pbclient && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/luchiz/pixelbuild/pbclient/main.cpp > CMakeFiles/pbclient.dir/main.cpp.i

pbclient/CMakeFiles/pbclient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/pbclient.dir/main.cpp.s"
	cd /home/luchiz/pixelbuild/debug/pbclient && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/luchiz/pixelbuild/pbclient/main.cpp -o CMakeFiles/pbclient.dir/main.cpp.s

# Object files for target pbclient
pbclient_OBJECTS = \
"CMakeFiles/pbclient.dir/main.cpp.o"

# External object files for target pbclient
pbclient_EXTERNAL_OBJECTS =

pbclient/pbclient: pbclient/CMakeFiles/pbclient.dir/main.cpp.o
pbclient/pbclient: pbclient/CMakeFiles/pbclient.dir/build.make
pbclient/pbclient: pbengine/libpbengine.so
pbclient/pbclient: /usr/local/lib/libsfml-graphics.so.2.6.1
pbclient/pbclient: /usr/local/lib/libsfml-window.so.2.6.1
pbclient/pbclient: /usr/local/lib/libsfml-network.so.2.6.1
pbclient/pbclient: /usr/local/lib/libsfml-system.so.2.6.1
pbclient/pbclient: pbclient/CMakeFiles/pbclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/luchiz/pixelbuild/debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pbclient"
	cd /home/luchiz/pixelbuild/debug/pbclient && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pbclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
pbclient/CMakeFiles/pbclient.dir/build: pbclient/pbclient
.PHONY : pbclient/CMakeFiles/pbclient.dir/build

pbclient/CMakeFiles/pbclient.dir/clean:
	cd /home/luchiz/pixelbuild/debug/pbclient && $(CMAKE_COMMAND) -P CMakeFiles/pbclient.dir/cmake_clean.cmake
.PHONY : pbclient/CMakeFiles/pbclient.dir/clean

pbclient/CMakeFiles/pbclient.dir/depend:
	cd /home/luchiz/pixelbuild/debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/luchiz/pixelbuild /home/luchiz/pixelbuild/pbclient /home/luchiz/pixelbuild/debug /home/luchiz/pixelbuild/debug/pbclient /home/luchiz/pixelbuild/debug/pbclient/CMakeFiles/pbclient.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : pbclient/CMakeFiles/pbclient.dir/depend

