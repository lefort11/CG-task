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
include CMakeFiles/multi-touch_static.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multi-touch_static.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multi-touch_static.dir/flags.make

CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o: CMakeFiles/multi-touch_static.dir/flags.make
CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o: ../progs/demos/multi-touch/multi-touch.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/progs/demos/multi-touch/multi-touch.c

CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/progs/demos/multi-touch/multi-touch.c > CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.i

CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/progs/demos/multi-touch/multi-touch.c -o CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.s

CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o.requires:

.PHONY : CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o.requires

CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o.provides: CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o.requires
	$(MAKE) -f CMakeFiles/multi-touch_static.dir/build.make CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o.provides.build
.PHONY : CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o.provides

CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o.provides.build: CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o


# Object files for target multi-touch_static
multi__touch_static_OBJECTS = \
"CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o"

# External object files for target multi-touch_static
multi__touch_static_EXTERNAL_OBJECTS =

bin/multi-touch_static: CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o
bin/multi-touch_static: CMakeFiles/multi-touch_static.dir/build.make
bin/multi-touch_static: /usr/X11R6/lib/libGLU.dylib
bin/multi-touch_static: /usr/X11R6/lib/libGL.dylib
bin/multi-touch_static: /usr/X11R6/lib/libSM.dylib
bin/multi-touch_static: /usr/X11R6/lib/libICE.dylib
bin/multi-touch_static: /usr/X11R6/lib/libX11.dylib
bin/multi-touch_static: /usr/X11R6/lib/libXext.dylib
bin/multi-touch_static: /usr/X11R6/lib/libXrandr.dylib
bin/multi-touch_static: /usr/X11R6/lib/libXxf86vm.dylib
bin/multi-touch_static: /usr/X11R6/lib/libXi.dylib
bin/multi-touch_static: lib/libglut.a
bin/multi-touch_static: /usr/X11R6/lib/libGL.dylib
bin/multi-touch_static: /usr/X11R6/lib/libSM.dylib
bin/multi-touch_static: /usr/X11R6/lib/libICE.dylib
bin/multi-touch_static: /usr/X11R6/lib/libX11.dylib
bin/multi-touch_static: /usr/X11R6/lib/libXext.dylib
bin/multi-touch_static: /usr/X11R6/lib/libXrandr.dylib
bin/multi-touch_static: /usr/X11R6/lib/libXxf86vm.dylib
bin/multi-touch_static: /usr/X11R6/lib/libXi.dylib
bin/multi-touch_static: CMakeFiles/multi-touch_static.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/multi-touch_static"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multi-touch_static.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multi-touch_static.dir/build: bin/multi-touch_static

.PHONY : CMakeFiles/multi-touch_static.dir/build

CMakeFiles/multi-touch_static.dir/requires: CMakeFiles/multi-touch_static.dir/progs/demos/multi-touch/multi-touch.c.o.requires

.PHONY : CMakeFiles/multi-touch_static.dir/requires

CMakeFiles/multi-touch_static.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multi-touch_static.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multi-touch_static.dir/clean

CMakeFiles/multi-touch_static.dir/depend:
	cd /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0 /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0 /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build /Users/Gleb/Desktop/mashgraph/ext/freeglut-3.0.0/build/CMakeFiles/multi-touch_static.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multi-touch_static.dir/depend

