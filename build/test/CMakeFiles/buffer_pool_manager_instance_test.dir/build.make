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

# Include any dependencies generated for this target.
include test/CMakeFiles/buffer_pool_manager_instance_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/buffer_pool_manager_instance_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/buffer_pool_manager_instance_test.dir/flags.make

test/CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.o: test/CMakeFiles/buffer_pool_manager_instance_test.dir/flags.make
test/CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.o: ../test/buffer/buffer_pool_manager_instance_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cky/Desktop/bust/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.o"
	cd /home/cky/Desktop/bust/build/test && /usr/bin/clang++-12  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.o -c /home/cky/Desktop/bust/test/buffer/buffer_pool_manager_instance_test.cpp

test/CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.i"
	cd /home/cky/Desktop/bust/build/test && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cky/Desktop/bust/test/buffer/buffer_pool_manager_instance_test.cpp > CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.i

test/CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.s"
	cd /home/cky/Desktop/bust/build/test && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cky/Desktop/bust/test/buffer/buffer_pool_manager_instance_test.cpp -o CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.s

# Object files for target buffer_pool_manager_instance_test
buffer_pool_manager_instance_test_OBJECTS = \
"CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.o"

# External object files for target buffer_pool_manager_instance_test
buffer_pool_manager_instance_test_EXTERNAL_OBJECTS =

test/buffer_pool_manager_instance_test: test/CMakeFiles/buffer_pool_manager_instance_test.dir/buffer/buffer_pool_manager_instance_test.cpp.o
test/buffer_pool_manager_instance_test: test/CMakeFiles/buffer_pool_manager_instance_test.dir/build.make
test/buffer_pool_manager_instance_test: lib/libbustub.a
test/buffer_pool_manager_instance_test: lib/libgtest.a
test/buffer_pool_manager_instance_test: lib/libgmock_main.a
test/buffer_pool_manager_instance_test: lib/libbustub_murmur3.a
test/buffer_pool_manager_instance_test: lib/libduckdb_pg_query.a
test/buffer_pool_manager_instance_test: lib/libfmtd.a
test/buffer_pool_manager_instance_test: lib/libfort.a
test/buffer_pool_manager_instance_test: lib/libgmock.a
test/buffer_pool_manager_instance_test: lib/libgtest.a
test/buffer_pool_manager_instance_test: test/CMakeFiles/buffer_pool_manager_instance_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cky/Desktop/bust/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable buffer_pool_manager_instance_test"
	cd /home/cky/Desktop/bust/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/buffer_pool_manager_instance_test.dir/link.txt --verbose=$(VERBOSE)
	cd /home/cky/Desktop/bust/build/test && /usr/bin/cmake -D TEST_TARGET=buffer_pool_manager_instance_test -D TEST_EXECUTABLE=/home/cky/Desktop/bust/build/test/buffer_pool_manager_instance_test -D TEST_EXECUTOR= -D TEST_WORKING_DIR=/home/cky/Desktop/bust/build/test -D "TEST_EXTRA_ARGS=--gtest_color=auto;--gtest_output=xml:/home/cky/Desktop/bust/build/test/buffer_pool_manager_instance_test.xml;--gtest_catch_exceptions=0" -D "TEST_PROPERTIES=TIMEOUT;120" -D TEST_PREFIX= -D TEST_SUFFIX= -D NO_PRETTY_TYPES=FALSE -D NO_PRETTY_VALUES=FALSE -D TEST_LIST=buffer_pool_manager_instance_test_TESTS -D CTEST_FILE=/home/cky/Desktop/bust/build/test/buffer_pool_manager_instance_test[1]_tests.cmake -D TEST_DISCOVERY_TIMEOUT=120 -P /usr/share/cmake-3.16/Modules/GoogleTestAddTests.cmake

# Rule to build all files generated by this target.
test/CMakeFiles/buffer_pool_manager_instance_test.dir/build: test/buffer_pool_manager_instance_test

.PHONY : test/CMakeFiles/buffer_pool_manager_instance_test.dir/build

test/CMakeFiles/buffer_pool_manager_instance_test.dir/clean:
	cd /home/cky/Desktop/bust/build/test && $(CMAKE_COMMAND) -P CMakeFiles/buffer_pool_manager_instance_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/buffer_pool_manager_instance_test.dir/clean

test/CMakeFiles/buffer_pool_manager_instance_test.dir/depend:
	cd /home/cky/Desktop/bust/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cky/Desktop/bust /home/cky/Desktop/bust/test /home/cky/Desktop/bust/build /home/cky/Desktop/bust/build/test /home/cky/Desktop/bust/build/test/CMakeFiles/buffer_pool_manager_instance_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/buffer_pool_manager_instance_test.dir/depend

