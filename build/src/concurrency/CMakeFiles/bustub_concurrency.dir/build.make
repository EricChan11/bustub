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
include src/concurrency/CMakeFiles/bustub_concurrency.dir/depend.make

# Include the progress variables for this target.
include src/concurrency/CMakeFiles/bustub_concurrency.dir/progress.make

# Include the compile flags for this target's objects.
include src/concurrency/CMakeFiles/bustub_concurrency.dir/flags.make

src/concurrency/CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.o: src/concurrency/CMakeFiles/bustub_concurrency.dir/flags.make
src/concurrency/CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.o: ../src/concurrency/lock_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cky/Desktop/bust/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/concurrency/CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.o"
	cd /home/cky/Desktop/bust/build/src/concurrency && /usr/bin/clang++-12  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.o -c /home/cky/Desktop/bust/src/concurrency/lock_manager.cpp

src/concurrency/CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.i"
	cd /home/cky/Desktop/bust/build/src/concurrency && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cky/Desktop/bust/src/concurrency/lock_manager.cpp > CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.i

src/concurrency/CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.s"
	cd /home/cky/Desktop/bust/build/src/concurrency && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cky/Desktop/bust/src/concurrency/lock_manager.cpp -o CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.s

src/concurrency/CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.o: src/concurrency/CMakeFiles/bustub_concurrency.dir/flags.make
src/concurrency/CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.o: ../src/concurrency/transaction_manager.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cky/Desktop/bust/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/concurrency/CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.o"
	cd /home/cky/Desktop/bust/build/src/concurrency && /usr/bin/clang++-12  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.o -c /home/cky/Desktop/bust/src/concurrency/transaction_manager.cpp

src/concurrency/CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.i"
	cd /home/cky/Desktop/bust/build/src/concurrency && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/cky/Desktop/bust/src/concurrency/transaction_manager.cpp > CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.i

src/concurrency/CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.s"
	cd /home/cky/Desktop/bust/build/src/concurrency && /usr/bin/clang++-12 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/cky/Desktop/bust/src/concurrency/transaction_manager.cpp -o CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.s

bustub_concurrency: src/concurrency/CMakeFiles/bustub_concurrency.dir/lock_manager.cpp.o
bustub_concurrency: src/concurrency/CMakeFiles/bustub_concurrency.dir/transaction_manager.cpp.o
bustub_concurrency: src/concurrency/CMakeFiles/bustub_concurrency.dir/build.make

.PHONY : bustub_concurrency

# Rule to build all files generated by this target.
src/concurrency/CMakeFiles/bustub_concurrency.dir/build: bustub_concurrency

.PHONY : src/concurrency/CMakeFiles/bustub_concurrency.dir/build

src/concurrency/CMakeFiles/bustub_concurrency.dir/clean:
	cd /home/cky/Desktop/bust/build/src/concurrency && $(CMAKE_COMMAND) -P CMakeFiles/bustub_concurrency.dir/cmake_clean.cmake
.PHONY : src/concurrency/CMakeFiles/bustub_concurrency.dir/clean

src/concurrency/CMakeFiles/bustub_concurrency.dir/depend:
	cd /home/cky/Desktop/bust/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cky/Desktop/bust /home/cky/Desktop/bust/src/concurrency /home/cky/Desktop/bust/build /home/cky/Desktop/bust/build/src/concurrency /home/cky/Desktop/bust/build/src/concurrency/CMakeFiles/bustub_concurrency.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/concurrency/CMakeFiles/bustub_concurrency.dir/depend

