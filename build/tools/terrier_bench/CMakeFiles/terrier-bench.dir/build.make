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
include tools/terrier_bench/CMakeFiles/terrier-bench.dir/depend.make

# Include the progress variables for this target.
include tools/terrier_bench/CMakeFiles/terrier-bench.dir/progress.make

# Include the compile flags for this target's objects.
include tools/terrier_bench/CMakeFiles/terrier-bench.dir/flags.make

tools/terrier_bench/CMakeFiles/terrier-bench.dir/terrier.cpp.o: tools/terrier_bench/CMakeFiles/terrier-bench.dir/flags.make
tools/terrier_bench/CMakeFiles/terrier-bench.dir/terrier.cpp.o: ../tools/terrier_bench/terrier.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cky/Desktop/bust/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tools/terrier_bench/CMakeFiles/terrier-bench.dir/terrier.cpp.o"
	cd /home/cky/Desktop/bust/build/tools/terrier_bench && /usr/bin/clang++-12  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/terrier-bench.dir/terrier.cpp.o -c /home/cky/Desktop/bust/tools/terrier_bench/terrier.cpp

tools/terrier_bench/CMakeFiles/terrier-bench.dir/terrier.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/terrier-bench.dir/terrier.cpp.i"
	cd /home/cky/Desktop/bust/build/tools/terrier_bench && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cky/Desktop/bust/tools/terrier_bench/terrier.cpp > CMakeFiles/terrier-bench.dir/terrier.cpp.i

tools/terrier_bench/CMakeFiles/terrier-bench.dir/terrier.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/terrier-bench.dir/terrier.cpp.s"
	cd /home/cky/Desktop/bust/build/tools/terrier_bench && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cky/Desktop/bust/tools/terrier_bench/terrier.cpp -o CMakeFiles/terrier-bench.dir/terrier.cpp.s

# Object files for target terrier-bench
terrier__bench_OBJECTS = \
"CMakeFiles/terrier-bench.dir/terrier.cpp.o"

# External object files for target terrier-bench
terrier__bench_EXTERNAL_OBJECTS =

bin/bustub-terrier-bench: tools/terrier_bench/CMakeFiles/terrier-bench.dir/terrier.cpp.o
bin/bustub-terrier-bench: tools/terrier_bench/CMakeFiles/terrier-bench.dir/build.make
bin/bustub-terrier-bench: lib/libbustub.a
bin/bustub-terrier-bench: lib/libbustub_murmur3.a
bin/bustub-terrier-bench: lib/libduckdb_pg_query.a
bin/bustub-terrier-bench: lib/libfmtd.a
bin/bustub-terrier-bench: lib/libfort.a
bin/bustub-terrier-bench: tools/terrier_bench/CMakeFiles/terrier-bench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cky/Desktop/bust/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/bustub-terrier-bench"
	cd /home/cky/Desktop/bust/build/tools/terrier_bench && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/terrier-bench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tools/terrier_bench/CMakeFiles/terrier-bench.dir/build: bin/bustub-terrier-bench

.PHONY : tools/terrier_bench/CMakeFiles/terrier-bench.dir/build

tools/terrier_bench/CMakeFiles/terrier-bench.dir/clean:
	cd /home/cky/Desktop/bust/build/tools/terrier_bench && $(CMAKE_COMMAND) -P CMakeFiles/terrier-bench.dir/cmake_clean.cmake
.PHONY : tools/terrier_bench/CMakeFiles/terrier-bench.dir/clean

tools/terrier_bench/CMakeFiles/terrier-bench.dir/depend:
	cd /home/cky/Desktop/bust/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cky/Desktop/bust /home/cky/Desktop/bust/tools/terrier_bench /home/cky/Desktop/bust/build /home/cky/Desktop/bust/build/tools/terrier_bench /home/cky/Desktop/bust/build/tools/terrier_bench/CMakeFiles/terrier-bench.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tools/terrier_bench/CMakeFiles/terrier-bench.dir/depend

