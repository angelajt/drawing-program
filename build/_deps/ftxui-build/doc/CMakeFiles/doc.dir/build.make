# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /root/workspace/drawing/final-project-angelajt

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/workspace/drawing/final-project-angelajt/build

# Utility rule file for doc.

# Include any custom commands dependencies for this target.
include _deps/ftxui-build/doc/CMakeFiles/doc.dir/compiler_depend.make

# Include the progress variables for this target.
include _deps/ftxui-build/doc/CMakeFiles/doc.dir/progress.make

_deps/ftxui-build/doc/CMakeFiles/doc:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/root/workspace/drawing/final-project-angelajt/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating API documentation with Doxygen"
	cd /root/workspace/drawing/final-project-angelajt/build/_deps/ftxui-build/doc && /usr/bin/doxygen /root/workspace/drawing/final-project-angelajt/build/_deps/ftxui-build/doc/Doxyfile

doc: _deps/ftxui-build/doc/CMakeFiles/doc
doc: _deps/ftxui-build/doc/CMakeFiles/doc.dir/build.make
.PHONY : doc

# Rule to build all files generated by this target.
_deps/ftxui-build/doc/CMakeFiles/doc.dir/build: doc
.PHONY : _deps/ftxui-build/doc/CMakeFiles/doc.dir/build

_deps/ftxui-build/doc/CMakeFiles/doc.dir/clean:
	cd /root/workspace/drawing/final-project-angelajt/build/_deps/ftxui-build/doc && $(CMAKE_COMMAND) -P CMakeFiles/doc.dir/cmake_clean.cmake
.PHONY : _deps/ftxui-build/doc/CMakeFiles/doc.dir/clean

_deps/ftxui-build/doc/CMakeFiles/doc.dir/depend:
	cd /root/workspace/drawing/final-project-angelajt/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/workspace/drawing/final-project-angelajt /root/workspace/drawing/final-project-angelajt/build/_deps/ftxui-src/doc /root/workspace/drawing/final-project-angelajt/build /root/workspace/drawing/final-project-angelajt/build/_deps/ftxui-build/doc /root/workspace/drawing/final-project-angelajt/build/_deps/ftxui-build/doc/CMakeFiles/doc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : _deps/ftxui-build/doc/CMakeFiles/doc.dir/depend

