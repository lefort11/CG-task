# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build

# Include any dependencies generated for this target.
include CMakeFiles/Fractals_static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Fractals_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Fractals_static.dir/flags.make

CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o: CMakeFiles/Fractals_static.dir/flags.make
CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o: ../progs/demos/Fractals/fractals.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/progs/demos/Fractals/fractals.c

CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/progs/demos/Fractals/fractals.c > CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.i

CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/progs/demos/Fractals/fractals.c -o CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.s

CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o.requires:

.PHONY : CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o.requires

CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o.provides: CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o.requires
	$(MAKE) -f CMakeFiles/Fractals_static.dir/build.make CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o.provides.build
.PHONY : CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o.provides

CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o.provides.build: CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o


# Object files for target Fractals_static
Fractals_static_OBJECTS = \
"CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o"

# External object files for target Fractals_static
Fractals_static_EXTERNAL_OBJECTS =

bin/Fractals_static: CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o
bin/Fractals_static: CMakeFiles/Fractals_static.dir/build.make
bin/Fractals_static: /usr/X11R6/lib/libGLU.dylib
bin/Fractals_static: /usr/X11R6/lib/libGL.dylib
bin/Fractals_static: /usr/X11R6/lib/libSM.dylib
bin/Fractals_static: /usr/X11R6/lib/libICE.dylib
bin/Fractals_static: /usr/X11R6/lib/libX11.dylib
bin/Fractals_static: /usr/X11R6/lib/libXext.dylib
bin/Fractals_static: /usr/X11R6/lib/libXrandr.dylib
bin/Fractals_static: /usr/X11R6/lib/libXxf86vm.dylib
bin/Fractals_static: /usr/X11R6/lib/libXi.dylib
bin/Fractals_static: lib/libglut.a
bin/Fractals_static: /usr/X11R6/lib/libGL.dylib
bin/Fractals_static: /usr/X11R6/lib/libSM.dylib
bin/Fractals_static: /usr/X11R6/lib/libICE.dylib
bin/Fractals_static: /usr/X11R6/lib/libX11.dylib
bin/Fractals_static: /usr/X11R6/lib/libXext.dylib
bin/Fractals_static: /usr/X11R6/lib/libXrandr.dylib
bin/Fractals_static: /usr/X11R6/lib/libXxf86vm.dylib
bin/Fractals_static: /usr/X11R6/lib/libXi.dylib
bin/Fractals_static: CMakeFiles/Fractals_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/Fractals_static"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Fractals_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Fractals_static.dir/build: bin/Fractals_static

.PHONY : CMakeFiles/Fractals_static.dir/build

CMakeFiles/Fractals_static.dir/requires: CMakeFiles/Fractals_static.dir/progs/demos/Fractals/fractals.c.o.requires

.PHONY : CMakeFiles/Fractals_static.dir/requires

CMakeFiles/Fractals_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Fractals_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Fractals_static.dir/clean

CMakeFiles/Fractals_static.dir/depend:
	cd /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0 /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0 /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build/CMakeFiles/Fractals_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Fractals_static.dir/depend

