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
include example/CMakeFiles/consumer.dir/depend.make

# Include the progress variables for this target.
include example/CMakeFiles/consumer.dir/progress.make

# Include the compile flags for this target's objects.
include example/CMakeFiles/consumer.dir/flags.make

example/CMakeFiles/consumer.dir/rpc/consumer.cpp.o: example/CMakeFiles/consumer.dir/flags.make
example/CMakeFiles/consumer.dir/rpc/consumer.cpp.o: ../example/rpc/consumer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ubuntu/SkyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object example/CMakeFiles/consumer.dir/rpc/consumer.cpp.o"
	cd /home/ubuntu/SkyRPC/build/example && /usr/bin/g++-11  $(CXX_DEFINES) -D__FILE__=\"example/rpc/consumer.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/consumer.dir/rpc/consumer.cpp.o -c /home/ubuntu/SkyRPC/example/rpc/consumer.cpp

example/CMakeFiles/consumer.dir/rpc/consumer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/consumer.dir/rpc/consumer.cpp.i"
	cd /home/ubuntu/SkyRPC/build/example && /usr/bin/g++-11 $(CXX_DEFINES) -D__FILE__=\"example/rpc/consumer.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ubuntu/SkyRPC/example/rpc/consumer.cpp > CMakeFiles/consumer.dir/rpc/consumer.cpp.i

example/CMakeFiles/consumer.dir/rpc/consumer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/consumer.dir/rpc/consumer.cpp.s"
	cd /home/ubuntu/SkyRPC/build/example && /usr/bin/g++-11 $(CXX_DEFINES) -D__FILE__=\"example/rpc/consumer.cpp\" $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ubuntu/SkyRPC/example/rpc/consumer.cpp -o CMakeFiles/consumer.dir/rpc/consumer.cpp.s

# Object files for target consumer
consumer_OBJECTS = \
"CMakeFiles/consumer.dir/rpc/consumer.cpp.o"

# External object files for target consumer
consumer_EXTERNAL_OBJECTS =

../bin/example/consumer: example/CMakeFiles/consumer.dir/rpc/consumer.cpp.o
../bin/example/consumer: example/CMakeFiles/consumer.dir/build.make
../bin/example/consumer: ../lib/libskyrpc.so
../bin/example/consumer: example/CMakeFiles/consumer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ubuntu/SkyRPC/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/example/consumer"
	cd /home/ubuntu/SkyRPC/build/example && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/consumer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
example/CMakeFiles/consumer.dir/build: ../bin/example/consumer

.PHONY : example/CMakeFiles/consumer.dir/build

example/CMakeFiles/consumer.dir/clean:
	cd /home/ubuntu/SkyRPC/build/example && $(CMAKE_COMMAND) -P CMakeFiles/consumer.dir/cmake_clean.cmake
.PHONY : example/CMakeFiles/consumer.dir/clean

example/CMakeFiles/consumer.dir/depend:
	cd /home/ubuntu/SkyRPC/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ubuntu/SkyRPC /home/ubuntu/SkyRPC/example /home/ubuntu/SkyRPC/build /home/ubuntu/SkyRPC/build/example /home/ubuntu/SkyRPC/build/example/CMakeFiles/consumer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : example/CMakeFiles/consumer.dir/depend

