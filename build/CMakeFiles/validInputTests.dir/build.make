# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.27.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.27.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/kaini/Documents/SEP/BLOCK14PG

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kaini/Documents/SEP/BLOCK14PG/build

# Include any dependencies generated for this target.
include CMakeFiles/validInputTests.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/validInputTests.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/validInputTests.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/validInputTests.dir/flags.make

CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/tests/unit/readInput/validTests.cpp
CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o -MF CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o.d -o CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/tests/unit/readInput/validTests.cpp

CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/tests/unit/readInput/validTests.cpp > CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.i

CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/tests/unit/readInput/validTests.cpp -o CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.s

CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/tests/unit/readInput/InputTestHelper.cpp
CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o -MF CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o.d -o CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/tests/unit/readInput/InputTestHelper.cpp

CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/tests/unit/readInput/InputTestHelper.cpp > CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.i

CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/tests/unit/readInput/InputTestHelper.cpp -o CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.s

CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/Block.cpp
CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o -MF CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o.d -o CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/Block.cpp

CMakeFiles/validInputTests.dir/src/cores/Block.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/src/cores/Block.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/Block.cpp > CMakeFiles/validInputTests.dir/src/cores/Block.cpp.i

CMakeFiles/validInputTests.dir/src/cores/Block.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/src/cores/Block.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/Block.cpp -o CMakeFiles/validInputTests.dir/src/cores/Block.cpp.s

CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/Cuboid.cpp
CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o -MF CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o.d -o CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/Cuboid.cpp

CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/Cuboid.cpp > CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.i

CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/Cuboid.cpp -o CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.s

CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/SafeInputTasks.cpp
CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o -MF CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o.d -o CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/SafeInputTasks.cpp

CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/SafeInputTasks.cpp > CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.i

CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/SafeInputTasks.cpp -o CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.s

CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/SafeOutputTasks.cpp
CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o -MF CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o.d -o CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/SafeOutputTasks.cpp

CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/SafeOutputTasks.cpp > CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.i

CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/src/cores/SafeOutputTasks.cpp -o CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.s

CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/src/globals/globals.cpp
CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o -MF CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o.d -o CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/src/globals/globals.cpp

CMakeFiles/validInputTests.dir/src/globals/globals.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/src/globals/globals.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/src/globals/globals.cpp > CMakeFiles/validInputTests.dir/src/globals/globals.cpp.i

CMakeFiles/validInputTests.dir/src/globals/globals.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/src/globals/globals.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/src/globals/globals.cpp -o CMakeFiles/validInputTests.dir/src/globals/globals.cpp.s

CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/src/input/readInput.cpp
CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o -MF CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o.d -o CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/src/input/readInput.cpp

CMakeFiles/validInputTests.dir/src/input/readInput.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/src/input/readInput.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/src/input/readInput.cpp > CMakeFiles/validInputTests.dir/src/input/readInput.cpp.i

CMakeFiles/validInputTests.dir/src/input/readInput.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/src/input/readInput.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/src/input/readInput.cpp -o CMakeFiles/validInputTests.dir/src/input/readInput.cpp.s

CMakeFiles/validInputTests.dir/src/output/output.cpp.o: CMakeFiles/validInputTests.dir/flags.make
CMakeFiles/validInputTests.dir/src/output/output.cpp.o: /Users/kaini/Documents/SEP/BLOCK14PG/src/output/output.cpp
CMakeFiles/validInputTests.dir/src/output/output.cpp.o: CMakeFiles/validInputTests.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/validInputTests.dir/src/output/output.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/validInputTests.dir/src/output/output.cpp.o -MF CMakeFiles/validInputTests.dir/src/output/output.cpp.o.d -o CMakeFiles/validInputTests.dir/src/output/output.cpp.o -c /Users/kaini/Documents/SEP/BLOCK14PG/src/output/output.cpp

CMakeFiles/validInputTests.dir/src/output/output.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/validInputTests.dir/src/output/output.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kaini/Documents/SEP/BLOCK14PG/src/output/output.cpp > CMakeFiles/validInputTests.dir/src/output/output.cpp.i

CMakeFiles/validInputTests.dir/src/output/output.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/validInputTests.dir/src/output/output.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kaini/Documents/SEP/BLOCK14PG/src/output/output.cpp -o CMakeFiles/validInputTests.dir/src/output/output.cpp.s

# Object files for target validInputTests
validInputTests_OBJECTS = \
"CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o" \
"CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o" \
"CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o" \
"CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o" \
"CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o" \
"CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o" \
"CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o" \
"CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o" \
"CMakeFiles/validInputTests.dir/src/output/output.cpp.o"

# External object files for target validInputTests
validInputTests_EXTERNAL_OBJECTS =

validInputTests: CMakeFiles/validInputTests.dir/tests/unit/readInput/validTests.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/tests/unit/readInput/InputTestHelper.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/src/cores/Block.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/src/cores/Cuboid.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/src/cores/SafeInputTasks.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/src/cores/SafeOutputTasks.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/src/globals/globals.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/src/input/readInput.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/src/output/output.cpp.o
validInputTests: CMakeFiles/validInputTests.dir/build.make
validInputTests: lib/libgtest.a
validInputTests: lib/libgtest_main.a
validInputTests: lib/libgtest.a
validInputTests: CMakeFiles/validInputTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable validInputTests"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/validInputTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/validInputTests.dir/build: validInputTests
.PHONY : CMakeFiles/validInputTests.dir/build

CMakeFiles/validInputTests.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/validInputTests.dir/cmake_clean.cmake
.PHONY : CMakeFiles/validInputTests.dir/clean

CMakeFiles/validInputTests.dir/depend:
	cd /Users/kaini/Documents/SEP/BLOCK14PG/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kaini/Documents/SEP/BLOCK14PG /Users/kaini/Documents/SEP/BLOCK14PG /Users/kaini/Documents/SEP/BLOCK14PG/build /Users/kaini/Documents/SEP/BLOCK14PG/build /Users/kaini/Documents/SEP/BLOCK14PG/build/CMakeFiles/validInputTests.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/validInputTests.dir/depend

