# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point

# Include any dependencies generated for this target.
include CMakeFiles/particles.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/particles.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/particles.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/particles.dir/flags.make

CMakeFiles/particles.dir/main.cc.o: CMakeFiles/particles.dir/flags.make
CMakeFiles/particles.dir/main.cc.o: main.cc
CMakeFiles/particles.dir/main.cc.o: CMakeFiles/particles.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/particles.dir/main.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/particles.dir/main.cc.o -MF CMakeFiles/particles.dir/main.cc.o.d -o CMakeFiles/particles.dir/main.cc.o -c /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point/main.cc

CMakeFiles/particles.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/particles.dir/main.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point/main.cc > CMakeFiles/particles.dir/main.cc.i

CMakeFiles/particles.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/particles.dir/main.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point/main.cc -o CMakeFiles/particles.dir/main.cc.s

# Object files for target particles
particles_OBJECTS = \
"CMakeFiles/particles.dir/main.cc.o"

# External object files for target particles
particles_EXTERNAL_OBJECTS =

particles: CMakeFiles/particles.dir/main.cc.o
particles: CMakeFiles/particles.dir/build.make
particles: lib/libgtest_main.a
particles: lib/libgtest.a
particles: libpart.a
particles: /usr/lib/x86_64-linux-gnu/libfftw3.so
particles: CMakeFiles/particles.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable particles"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/particles.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/particles.dir/build: particles
.PHONY : CMakeFiles/particles.dir/build

CMakeFiles/particles.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/particles.dir/cmake_clean.cmake
.PHONY : CMakeFiles/particles.dir/clean

CMakeFiles/particles.dir/depend:
	cd /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point /home/thomashenzel/SP4E/homework3/heat-fft-solver/starting_point/CMakeFiles/particles.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/particles.dir/depend

