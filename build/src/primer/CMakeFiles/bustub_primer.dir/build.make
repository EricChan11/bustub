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
include src/primer/CMakeFiles/bustub_primer.dir/depend.make

# Include the progress variables for this target.
include src/primer/CMakeFiles/bustub_primer.dir/progress.make

# Include the compile flags for this target's objects.
include src/primer/CMakeFiles/bustub_primer.dir/flags.make

src/primer/CMakeFiles/bustub_primer.dir/p0_trie.cpp.o: src/primer/CMakeFiles/bustub_primer.dir/flags.make
src/primer/CMakeFiles/bustub_primer.dir/p0_trie.cpp.o: ../src/primer/p0_trie.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cky/Desktop/bust/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/primer/CMakeFiles/bustub_primer.dir/p0_trie.cpp.o"
	cd /home/cky/Desktop/bust/build/src/primer && /usr/bin/clang++-12  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bustub_primer.dir/p0_trie.cpp.o -c /home/cky/Desktop/bust/src/primer/p0_trie.cpp

src/primer/CMakeFiles/bustub_primer.dir/p0_trie.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_primer.dir/p0_trie.cpp.i"
	cd /home/cky/Desktop/bust/build/src/primer && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cky/Desktop/bust/src/primer/p0_trie.cpp > CMakeFiles/bustub_primer.dir/p0_trie.cpp.i

src/primer/CMakeFiles/bustub_primer.dir/p0_trie.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_primer.dir/p0_trie.cpp.s"
	cd /home/cky/Desktop/bust/build/src/primer && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cky/Desktop/bust/src/primer/p0_trie.cpp -o CMakeFiles/bustub_primer.dir/p0_trie.cpp.s

bustub_primer: src/primer/CMakeFiles/bustub_primer.dir/p0_trie.cpp.o
bustub_primer: src/primer/CMakeFiles/bustub_primer.dir/build.make

.PHONY : bustub_primer

# Rule to build all files generated by this target.
src/primer/CMakeFiles/bustub_primer.dir/build: bustub_primer

.PHONY : src/primer/CMakeFiles/bustub_primer.dir/build

src/primer/CMakeFiles/bustub_primer.dir/clean:
	cd /home/cky/Desktop/bust/build/src/primer && $(CMAKE_COMMAND) -P CMakeFiles/bustub_primer.dir/cmake_clean.cmake
.PHONY : src/primer/CMakeFiles/bustub_primer.dir/clean

src/primer/CMakeFiles/bustub_primer.dir/depend:
	cd /home/cky/Desktop/bust/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cky/Desktop/bust /home/cky/Desktop/bust/src/primer /home/cky/Desktop/bust/build /home/cky/Desktop/bust/build/src/primer /home/cky/Desktop/bust/build/src/primer/CMakeFiles/bustub_primer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/primer/CMakeFiles/bustub_primer.dir/depend

