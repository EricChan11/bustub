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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/cky/Desktop/bust

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cky/Desktop/bust/build

# Utility rule file for p3.16-integration-2_test.

# Include the progress variables for this target.
include test/CMakeFiles/p3.16-integration-2_test.dir/progress.make

test/CMakeFiles/p3.16-integration-2_test:
	cd /home/cky/Desktop/bust/build/test && ../bin/bustub-sqllogictest /home/cky/Desktop/bust/test/sql/p3.16-integration-2.slt --verbose -d --in-memory

p3.16-integration-2_test: test/CMakeFiles/p3.16-integration-2_test
p3.16-integration-2_test: test/CMakeFiles/p3.16-integration-2_test.dir/build.make

.PHONY : p3.16-integration-2_test

# Rule to build all files generated by this target.
test/CMakeFiles/p3.16-integration-2_test.dir/build: p3.16-integration-2_test

.PHONY : test/CMakeFiles/p3.16-integration-2_test.dir/build

test/CMakeFiles/p3.16-integration-2_test.dir/clean:
	cd /home/cky/Desktop/bust/build/test && $(CMAKE_COMMAND) -P CMakeFiles/p3.16-integration-2_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/p3.16-integration-2_test.dir/clean

test/CMakeFiles/p3.16-integration-2_test.dir/depend:
	cd /home/cky/Desktop/bust/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cky/Desktop/bust /home/cky/Desktop/bust/test /home/cky/Desktop/bust/build /home/cky/Desktop/bust/build/test /home/cky/Desktop/bust/build/test/CMakeFiles/p3.16-integration-2_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/p3.16-integration-2_test.dir/depend

