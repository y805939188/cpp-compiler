# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/4paradigm/Desktop/cpp-compiler

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/4paradigm/Desktop/cpp-compiler/build

# Include any dependencies generated for this target.
include lexer/CMakeFiles/token.dir/depend.make

# Include the progress variables for this target.
include lexer/CMakeFiles/token.dir/progress.make

# Include the compile flags for this target's objects.
include lexer/CMakeFiles/token.dir/flags.make

lexer/CMakeFiles/token.dir/src/lexer/token.cpp.o: lexer/CMakeFiles/token.dir/flags.make
lexer/CMakeFiles/token.dir/src/lexer/token.cpp.o: ../lexer/src/lexer/token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/4paradigm/Desktop/cpp-compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lexer/CMakeFiles/token.dir/src/lexer/token.cpp.o"
	cd /Users/4paradigm/Desktop/cpp-compiler/build/lexer && /usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/token.dir/src/lexer/token.cpp.o -c /Users/4paradigm/Desktop/cpp-compiler/lexer/src/lexer/token.cpp

lexer/CMakeFiles/token.dir/src/lexer/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/token.dir/src/lexer/token.cpp.i"
	cd /Users/4paradigm/Desktop/cpp-compiler/build/lexer && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/4paradigm/Desktop/cpp-compiler/lexer/src/lexer/token.cpp > CMakeFiles/token.dir/src/lexer/token.cpp.i

lexer/CMakeFiles/token.dir/src/lexer/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/token.dir/src/lexer/token.cpp.s"
	cd /Users/4paradigm/Desktop/cpp-compiler/build/lexer && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/4paradigm/Desktop/cpp-compiler/lexer/src/lexer/token.cpp -o CMakeFiles/token.dir/src/lexer/token.cpp.s

# Object files for target token
token_OBJECTS = \
"CMakeFiles/token.dir/src/lexer/token.cpp.o"

# External object files for target token
token_EXTERNAL_OBJECTS =

lexer/libtoken.a: lexer/CMakeFiles/token.dir/src/lexer/token.cpp.o
lexer/libtoken.a: lexer/CMakeFiles/token.dir/build.make
lexer/libtoken.a: lexer/CMakeFiles/token.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/4paradigm/Desktop/cpp-compiler/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libtoken.a"
	cd /Users/4paradigm/Desktop/cpp-compiler/build/lexer && $(CMAKE_COMMAND) -P CMakeFiles/token.dir/cmake_clean_target.cmake
	cd /Users/4paradigm/Desktop/cpp-compiler/build/lexer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/token.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lexer/CMakeFiles/token.dir/build: lexer/libtoken.a

.PHONY : lexer/CMakeFiles/token.dir/build

lexer/CMakeFiles/token.dir/clean:
	cd /Users/4paradigm/Desktop/cpp-compiler/build/lexer && $(CMAKE_COMMAND) -P CMakeFiles/token.dir/cmake_clean.cmake
.PHONY : lexer/CMakeFiles/token.dir/clean

lexer/CMakeFiles/token.dir/depend:
	cd /Users/4paradigm/Desktop/cpp-compiler/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/4paradigm/Desktop/cpp-compiler /Users/4paradigm/Desktop/cpp-compiler/lexer /Users/4paradigm/Desktop/cpp-compiler/build /Users/4paradigm/Desktop/cpp-compiler/build/lexer /Users/4paradigm/Desktop/cpp-compiler/build/lexer/CMakeFiles/token.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lexer/CMakeFiles/token.dir/depend
