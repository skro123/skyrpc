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


# Produce verbose output by default.
VERBOSE = 1

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ubuntu/SkyRPC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ubuntu/SkyRPC/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_http_connection.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_http_connection.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_http_connection.dir/flags.make

tests/CMakeFiles/test_http_connection.dir/test_http_connection.cpp.o: tests/CMakeFiles/test_http_connection.dir/flags.make
tests/CMakeFiles/test_http_connection.dir/test_http_connection.cpp.o: ../tests/test_http_connection.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/SkyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_http_connection.dir/test_http_connection.cpp.o"
	cd /home/ubuntu/SkyRPC/build/tests && /usr/bin/g++-11  $(CXX_DEFINES) -D__FILE__=\"tests/test_http_connection.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_http_connection.dir/test_http_connection.cpp.o -c /home/ubuntu/SkyRPC/tests/test_http_connection.cpp

tests/CMakeFiles/test_http_connection.dir/test_http_connection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_http_connection.dir/test_http_connection.cpp.i"
	cd /home/ubuntu/SkyRPC/build/tests && /usr/bin/g++-11 $(CXX_DEFINES) -D__FILE__=\"tests/test_http_connection.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/SkyRPC/tests/test_http_connection.cpp > CMakeFiles/test_http_connection.dir/test_http_connection.cpp.i

tests/CMakeFiles/test_http_connection.dir/test_http_connection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_http_connection.dir/test_http_connection.cpp.s"
	cd /home/ubuntu/SkyRPC/build/tests && /usr/bin/g++-11 $(CXX_DEFINES) -D__FILE__=\"tests/test_http_connection.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/SkyRPC/tests/test_http_connection.cpp -o CMakeFiles/test_http_connection.dir/test_http_connection.cpp.s

# Object files for target test_http_connection
test_http_connection_OBJECTS = \
"CMakeFiles/test_http_connection.dir/test_http_connection.cpp.o"

# External object files for target test_http_connection
test_http_connection_EXTERNAL_OBJECTS =

../bin/test/test_http_connection: tests/CMakeFiles/test_http_connection.dir/test_http_connection.cpp.o
../bin/test/test_http_connection: tests/CMakeFiles/test_http_connection.dir/build.make
../bin/test/test_http_connection: ../lib/libskyrpc.so
../bin/test/test_http_connection: tests/CMakeFiles/test_http_connection.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/SkyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/test/test_http_connection"
	cd /home/ubuntu/SkyRPC/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_http_connection.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_http_connection.dir/build: ../bin/test/test_http_connection

.PHONY : tests/CMakeFiles/test_http_connection.dir/build

tests/CMakeFiles/test_http_connection.dir/clean:
	cd /home/ubuntu/SkyRPC/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_http_connection.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_http_connection.dir/clean

tests/CMakeFiles/test_http_connection.dir/depend:
	cd /home/ubuntu/SkyRPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/SkyRPC /home/ubuntu/SkyRPC/tests /home/ubuntu/SkyRPC/build /home/ubuntu/SkyRPC/build/tests /home/ubuntu/SkyRPC/build/tests/CMakeFiles/test_http_connection.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_http_connection.dir/depend
