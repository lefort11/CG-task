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
CMAKE_SOURCE_DIR = /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build

# Include any dependencies generated for this target.
include src/CMakeFiles/glfw.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/glfw.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/glfw.dir/flags.make

src/CMakeFiles/glfw.dir/context.c.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/context.c.o: ../src/context.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/CMakeFiles/glfw.dir/context.c.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/context.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/context.c

src/CMakeFiles/glfw.dir/context.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/context.c.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/context.c > CMakeFiles/glfw.dir/context.c.i

src/CMakeFiles/glfw.dir/context.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/context.c.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/context.c -o CMakeFiles/glfw.dir/context.c.s

src/CMakeFiles/glfw.dir/context.c.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/context.c.o.requires

src/CMakeFiles/glfw.dir/context.c.o.provides: src/CMakeFiles/glfw.dir/context.c.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/context.c.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/context.c.o.provides

src/CMakeFiles/glfw.dir/context.c.o.provides.build: src/CMakeFiles/glfw.dir/context.c.o


src/CMakeFiles/glfw.dir/init.c.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/init.c.o: ../src/init.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object src/CMakeFiles/glfw.dir/init.c.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/init.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/init.c

src/CMakeFiles/glfw.dir/init.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/init.c.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/init.c > CMakeFiles/glfw.dir/init.c.i

src/CMakeFiles/glfw.dir/init.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/init.c.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/init.c -o CMakeFiles/glfw.dir/init.c.s

src/CMakeFiles/glfw.dir/init.c.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/init.c.o.requires

src/CMakeFiles/glfw.dir/init.c.o.provides: src/CMakeFiles/glfw.dir/init.c.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/init.c.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/init.c.o.provides

src/CMakeFiles/glfw.dir/init.c.o.provides.build: src/CMakeFiles/glfw.dir/init.c.o


src/CMakeFiles/glfw.dir/input.c.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/input.c.o: ../src/input.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object src/CMakeFiles/glfw.dir/input.c.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/input.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/input.c

src/CMakeFiles/glfw.dir/input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/input.c.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/input.c > CMakeFiles/glfw.dir/input.c.i

src/CMakeFiles/glfw.dir/input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/input.c.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/input.c -o CMakeFiles/glfw.dir/input.c.s

src/CMakeFiles/glfw.dir/input.c.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/input.c.o.requires

src/CMakeFiles/glfw.dir/input.c.o.provides: src/CMakeFiles/glfw.dir/input.c.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/input.c.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/input.c.o.provides

src/CMakeFiles/glfw.dir/input.c.o.provides.build: src/CMakeFiles/glfw.dir/input.c.o


src/CMakeFiles/glfw.dir/monitor.c.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/monitor.c.o: ../src/monitor.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object src/CMakeFiles/glfw.dir/monitor.c.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/monitor.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/monitor.c

src/CMakeFiles/glfw.dir/monitor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/monitor.c.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/monitor.c > CMakeFiles/glfw.dir/monitor.c.i

src/CMakeFiles/glfw.dir/monitor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/monitor.c.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/monitor.c -o CMakeFiles/glfw.dir/monitor.c.s

src/CMakeFiles/glfw.dir/monitor.c.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/monitor.c.o.requires

src/CMakeFiles/glfw.dir/monitor.c.o.provides: src/CMakeFiles/glfw.dir/monitor.c.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/monitor.c.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/monitor.c.o.provides

src/CMakeFiles/glfw.dir/monitor.c.o.provides.build: src/CMakeFiles/glfw.dir/monitor.c.o


src/CMakeFiles/glfw.dir/vulkan.c.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/vulkan.c.o: ../src/vulkan.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object src/CMakeFiles/glfw.dir/vulkan.c.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/vulkan.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/vulkan.c

src/CMakeFiles/glfw.dir/vulkan.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/vulkan.c.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/vulkan.c > CMakeFiles/glfw.dir/vulkan.c.i

src/CMakeFiles/glfw.dir/vulkan.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/vulkan.c.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/vulkan.c -o CMakeFiles/glfw.dir/vulkan.c.s

src/CMakeFiles/glfw.dir/vulkan.c.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/vulkan.c.o.requires

src/CMakeFiles/glfw.dir/vulkan.c.o.provides: src/CMakeFiles/glfw.dir/vulkan.c.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/vulkan.c.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/vulkan.c.o.provides

src/CMakeFiles/glfw.dir/vulkan.c.o.provides.build: src/CMakeFiles/glfw.dir/vulkan.c.o


src/CMakeFiles/glfw.dir/window.c.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/window.c.o: ../src/window.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object src/CMakeFiles/glfw.dir/window.c.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/window.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/window.c

src/CMakeFiles/glfw.dir/window.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/window.c.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/window.c > CMakeFiles/glfw.dir/window.c.i

src/CMakeFiles/glfw.dir/window.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/window.c.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/window.c -o CMakeFiles/glfw.dir/window.c.s

src/CMakeFiles/glfw.dir/window.c.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/window.c.o.requires

src/CMakeFiles/glfw.dir/window.c.o.provides: src/CMakeFiles/glfw.dir/window.c.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/window.c.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/window.c.o.provides

src/CMakeFiles/glfw.dir/window.c.o.provides.build: src/CMakeFiles/glfw.dir/window.c.o


src/CMakeFiles/glfw.dir/cocoa_init.m.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/cocoa_init.m.o: ../src/cocoa_init.m
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object src/CMakeFiles/glfw.dir/cocoa_init.m.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/cocoa_init.m.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_init.m

src/CMakeFiles/glfw.dir/cocoa_init.m.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/cocoa_init.m.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_init.m > CMakeFiles/glfw.dir/cocoa_init.m.i

src/CMakeFiles/glfw.dir/cocoa_init.m.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/cocoa_init.m.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_init.m -o CMakeFiles/glfw.dir/cocoa_init.m.s

src/CMakeFiles/glfw.dir/cocoa_init.m.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/cocoa_init.m.o.requires

src/CMakeFiles/glfw.dir/cocoa_init.m.o.provides: src/CMakeFiles/glfw.dir/cocoa_init.m.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/cocoa_init.m.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/cocoa_init.m.o.provides

src/CMakeFiles/glfw.dir/cocoa_init.m.o.provides.build: src/CMakeFiles/glfw.dir/cocoa_init.m.o


src/CMakeFiles/glfw.dir/cocoa_joystick.m.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/cocoa_joystick.m.o: ../src/cocoa_joystick.m
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object src/CMakeFiles/glfw.dir/cocoa_joystick.m.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/cocoa_joystick.m.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_joystick.m

src/CMakeFiles/glfw.dir/cocoa_joystick.m.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/cocoa_joystick.m.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_joystick.m > CMakeFiles/glfw.dir/cocoa_joystick.m.i

src/CMakeFiles/glfw.dir/cocoa_joystick.m.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/cocoa_joystick.m.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_joystick.m -o CMakeFiles/glfw.dir/cocoa_joystick.m.s

src/CMakeFiles/glfw.dir/cocoa_joystick.m.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/cocoa_joystick.m.o.requires

src/CMakeFiles/glfw.dir/cocoa_joystick.m.o.provides: src/CMakeFiles/glfw.dir/cocoa_joystick.m.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/cocoa_joystick.m.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/cocoa_joystick.m.o.provides

src/CMakeFiles/glfw.dir/cocoa_joystick.m.o.provides.build: src/CMakeFiles/glfw.dir/cocoa_joystick.m.o


src/CMakeFiles/glfw.dir/cocoa_monitor.m.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/cocoa_monitor.m.o: ../src/cocoa_monitor.m
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building C object src/CMakeFiles/glfw.dir/cocoa_monitor.m.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/cocoa_monitor.m.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_monitor.m

src/CMakeFiles/glfw.dir/cocoa_monitor.m.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/cocoa_monitor.m.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_monitor.m > CMakeFiles/glfw.dir/cocoa_monitor.m.i

src/CMakeFiles/glfw.dir/cocoa_monitor.m.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/cocoa_monitor.m.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_monitor.m -o CMakeFiles/glfw.dir/cocoa_monitor.m.s

src/CMakeFiles/glfw.dir/cocoa_monitor.m.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/cocoa_monitor.m.o.requires

src/CMakeFiles/glfw.dir/cocoa_monitor.m.o.provides: src/CMakeFiles/glfw.dir/cocoa_monitor.m.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/cocoa_monitor.m.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/cocoa_monitor.m.o.provides

src/CMakeFiles/glfw.dir/cocoa_monitor.m.o.provides.build: src/CMakeFiles/glfw.dir/cocoa_monitor.m.o


src/CMakeFiles/glfw.dir/cocoa_window.m.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/cocoa_window.m.o: ../src/cocoa_window.m
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building C object src/CMakeFiles/glfw.dir/cocoa_window.m.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/cocoa_window.m.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_window.m

src/CMakeFiles/glfw.dir/cocoa_window.m.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/cocoa_window.m.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_window.m > CMakeFiles/glfw.dir/cocoa_window.m.i

src/CMakeFiles/glfw.dir/cocoa_window.m.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/cocoa_window.m.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_window.m -o CMakeFiles/glfw.dir/cocoa_window.m.s

src/CMakeFiles/glfw.dir/cocoa_window.m.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/cocoa_window.m.o.requires

src/CMakeFiles/glfw.dir/cocoa_window.m.o.provides: src/CMakeFiles/glfw.dir/cocoa_window.m.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/cocoa_window.m.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/cocoa_window.m.o.provides

src/CMakeFiles/glfw.dir/cocoa_window.m.o.provides.build: src/CMakeFiles/glfw.dir/cocoa_window.m.o


src/CMakeFiles/glfw.dir/cocoa_time.c.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/cocoa_time.c.o: ../src/cocoa_time.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building C object src/CMakeFiles/glfw.dir/cocoa_time.c.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/cocoa_time.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_time.c

src/CMakeFiles/glfw.dir/cocoa_time.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/cocoa_time.c.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_time.c > CMakeFiles/glfw.dir/cocoa_time.c.i

src/CMakeFiles/glfw.dir/cocoa_time.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/cocoa_time.c.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/cocoa_time.c -o CMakeFiles/glfw.dir/cocoa_time.c.s

src/CMakeFiles/glfw.dir/cocoa_time.c.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/cocoa_time.c.o.requires

src/CMakeFiles/glfw.dir/cocoa_time.c.o.provides: src/CMakeFiles/glfw.dir/cocoa_time.c.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/cocoa_time.c.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/cocoa_time.c.o.provides

src/CMakeFiles/glfw.dir/cocoa_time.c.o.provides.build: src/CMakeFiles/glfw.dir/cocoa_time.c.o


src/CMakeFiles/glfw.dir/posix_tls.c.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/posix_tls.c.o: ../src/posix_tls.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building C object src/CMakeFiles/glfw.dir/posix_tls.c.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/posix_tls.c.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/posix_tls.c

src/CMakeFiles/glfw.dir/posix_tls.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/posix_tls.c.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/posix_tls.c > CMakeFiles/glfw.dir/posix_tls.c.i

src/CMakeFiles/glfw.dir/posix_tls.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/posix_tls.c.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/posix_tls.c -o CMakeFiles/glfw.dir/posix_tls.c.s

src/CMakeFiles/glfw.dir/posix_tls.c.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/posix_tls.c.o.requires

src/CMakeFiles/glfw.dir/posix_tls.c.o.provides: src/CMakeFiles/glfw.dir/posix_tls.c.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/posix_tls.c.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/posix_tls.c.o.provides

src/CMakeFiles/glfw.dir/posix_tls.c.o.provides.build: src/CMakeFiles/glfw.dir/posix_tls.c.o


src/CMakeFiles/glfw.dir/nsgl_context.m.o: src/CMakeFiles/glfw.dir/flags.make
src/CMakeFiles/glfw.dir/nsgl_context.m.o: ../src/nsgl_context.m
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building C object src/CMakeFiles/glfw.dir/nsgl_context.m.o"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/glfw.dir/nsgl_context.m.o   -c /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/nsgl_context.m

src/CMakeFiles/glfw.dir/nsgl_context.m.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/glfw.dir/nsgl_context.m.i"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/nsgl_context.m > CMakeFiles/glfw.dir/nsgl_context.m.i

src/CMakeFiles/glfw.dir/nsgl_context.m.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/glfw.dir/nsgl_context.m.s"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src/nsgl_context.m -o CMakeFiles/glfw.dir/nsgl_context.m.s

src/CMakeFiles/glfw.dir/nsgl_context.m.o.requires:

.PHONY : src/CMakeFiles/glfw.dir/nsgl_context.m.o.requires

src/CMakeFiles/glfw.dir/nsgl_context.m.o.provides: src/CMakeFiles/glfw.dir/nsgl_context.m.o.requires
	$(MAKE) -f src/CMakeFiles/glfw.dir/build.make src/CMakeFiles/glfw.dir/nsgl_context.m.o.provides.build
.PHONY : src/CMakeFiles/glfw.dir/nsgl_context.m.o.provides

src/CMakeFiles/glfw.dir/nsgl_context.m.o.provides.build: src/CMakeFiles/glfw.dir/nsgl_context.m.o


# Object files for target glfw
glfw_OBJECTS = \
"CMakeFiles/glfw.dir/context.c.o" \
"CMakeFiles/glfw.dir/init.c.o" \
"CMakeFiles/glfw.dir/input.c.o" \
"CMakeFiles/glfw.dir/monitor.c.o" \
"CMakeFiles/glfw.dir/vulkan.c.o" \
"CMakeFiles/glfw.dir/window.c.o" \
"CMakeFiles/glfw.dir/cocoa_init.m.o" \
"CMakeFiles/glfw.dir/cocoa_joystick.m.o" \
"CMakeFiles/glfw.dir/cocoa_monitor.m.o" \
"CMakeFiles/glfw.dir/cocoa_window.m.o" \
"CMakeFiles/glfw.dir/cocoa_time.c.o" \
"CMakeFiles/glfw.dir/posix_tls.c.o" \
"CMakeFiles/glfw.dir/nsgl_context.m.o"

# External object files for target glfw
glfw_EXTERNAL_OBJECTS =

src/libglfw3.a: src/CMakeFiles/glfw.dir/context.c.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/init.c.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/input.c.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/monitor.c.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/vulkan.c.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/window.c.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/cocoa_init.m.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/cocoa_joystick.m.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/cocoa_monitor.m.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/cocoa_window.m.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/cocoa_time.c.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/posix_tls.c.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/nsgl_context.m.o
src/libglfw3.a: src/CMakeFiles/glfw.dir/build.make
src/libglfw3.a: src/CMakeFiles/glfw.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Linking C static library libglfw3.a"
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && $(CMAKE_COMMAND) -P CMakeFiles/glfw.dir/cmake_clean_target.cmake
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glfw.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/glfw.dir/build: src/libglfw3.a

.PHONY : src/CMakeFiles/glfw.dir/build

src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/context.c.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/init.c.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/input.c.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/monitor.c.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/vulkan.c.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/window.c.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/cocoa_init.m.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/cocoa_joystick.m.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/cocoa_monitor.m.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/cocoa_window.m.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/cocoa_time.c.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/posix_tls.c.o.requires
src/CMakeFiles/glfw.dir/requires: src/CMakeFiles/glfw.dir/nsgl_context.m.o.requires

.PHONY : src/CMakeFiles/glfw.dir/requires

src/CMakeFiles/glfw.dir/clean:
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src && $(CMAKE_COMMAND) -P CMakeFiles/glfw.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/glfw.dir/clean

src/CMakeFiles/glfw.dir/depend:
	cd /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1 /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/src /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src /Users/Gleb/Desktop/mashgraph/ext/glfw-3.2.1/build/src/CMakeFiles/glfw.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/glfw.dir/depend

