# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/fason/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7846.88/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/fason/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/201.7846.88/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/fason/dev/c_plus_plus/CMake/gclog

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/fason/dev/c_plus_plus/CMake/gclog/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Gclog.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Gclog.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Gclog.dir/flags.make

CMakeFiles/Gclog.dir/main.cpp.o: CMakeFiles/Gclog.dir/flags.make
CMakeFiles/Gclog.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/fason/dev/c_plus_plus/CMake/gclog/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Gclog.dir/main.cpp.o"
	/usr/local/gcc-9.3/bin/g++-9.3  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Gclog.dir/main.cpp.o -c /home/fason/dev/c_plus_plus/CMake/gclog/main.cpp

CMakeFiles/Gclog.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Gclog.dir/main.cpp.i"
	/usr/local/gcc-9.3/bin/g++-9.3 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/fason/dev/c_plus_plus/CMake/gclog/main.cpp > CMakeFiles/Gclog.dir/main.cpp.i

CMakeFiles/Gclog.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Gclog.dir/main.cpp.s"
	/usr/local/gcc-9.3/bin/g++-9.3 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/fason/dev/c_plus_plus/CMake/gclog/main.cpp -o CMakeFiles/Gclog.dir/main.cpp.s

# Object files for target Gclog
Gclog_OBJECTS = \
"CMakeFiles/Gclog.dir/main.cpp.o"

# External object files for target Gclog
Gclog_EXTERNAL_OBJECTS =

Gclog: CMakeFiles/Gclog.dir/main.cpp.o
Gclog: CMakeFiles/Gclog.dir/build.make
Gclog: CMakeFiles/Gclog.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/fason/dev/c_plus_plus/CMake/gclog/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Gclog"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Gclog.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Gclog.dir/build: Gclog

.PHONY : CMakeFiles/Gclog.dir/build

CMakeFiles/Gclog.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Gclog.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Gclog.dir/clean

CMakeFiles/Gclog.dir/depend:
	cd /home/fason/dev/c_plus_plus/CMake/gclog/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/fason/dev/c_plus_plus/CMake/gclog /home/fason/dev/c_plus_plus/CMake/gclog /home/fason/dev/c_plus_plus/CMake/gclog/cmake-build-debug /home/fason/dev/c_plus_plus/CMake/gclog/cmake-build-debug /home/fason/dev/c_plus_plus/CMake/gclog/cmake-build-debug/CMakeFiles/Gclog.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Gclog.dir/depend

