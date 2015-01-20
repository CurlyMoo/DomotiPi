# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /pilight

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /pilight

# Include any dependencies generated for this target.
include CMakeFiles/pilight-uuid.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pilight-uuid.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pilight-uuid.dir/flags.make

CMakeFiles/pilight-uuid.dir/uuid.c.o: uuid.c
	$(CMAKE_COMMAND) -E cmake_progress_report /pilight/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building C object CMakeFiles/pilight-uuid.dir/uuid.c.o"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -o CMakeFiles/pilight-uuid.dir/uuid.c.o   -c /pilight/uuid.c

CMakeFiles/pilight-uuid.dir/uuid.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/pilight-uuid.dir/uuid.c.i"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -E /pilight/uuid.c > CMakeFiles/pilight-uuid.dir/uuid.c.i

CMakeFiles/pilight-uuid.dir/uuid.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/pilight-uuid.dir/uuid.c.s"
	/usr/bin/gcc  $(C_DEFINES) $(C_FLAGS) -S /pilight/uuid.c -o CMakeFiles/pilight-uuid.dir/uuid.c.s

CMakeFiles/pilight-uuid.dir/uuid.c.o.requires:
.PHONY : CMakeFiles/pilight-uuid.dir/uuid.c.o.requires

CMakeFiles/pilight-uuid.dir/uuid.c.o.provides: CMakeFiles/pilight-uuid.dir/uuid.c.o.requires
	$(MAKE) -f CMakeFiles/pilight-uuid.dir/build.make CMakeFiles/pilight-uuid.dir/uuid.c.o.provides.build
.PHONY : CMakeFiles/pilight-uuid.dir/uuid.c.o.provides

CMakeFiles/pilight-uuid.dir/uuid.c.o.provides.build: CMakeFiles/pilight-uuid.dir/uuid.c.o

# Object files for target pilight-uuid
pilight__uuid_OBJECTS = \
"CMakeFiles/pilight-uuid.dir/uuid.c.o"

# External object files for target pilight-uuid
pilight__uuid_EXTERNAL_OBJECTS =

pilight-uuid: CMakeFiles/pilight-uuid.dir/uuid.c.o
pilight-uuid: libpilight.so
pilight-uuid: /usr/lib/arm-linux-gnueabihf/libz.so
pilight-uuid: CMakeFiles/pilight-uuid.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable pilight-uuid"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pilight-uuid.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pilight-uuid.dir/build: pilight-uuid
.PHONY : CMakeFiles/pilight-uuid.dir/build

CMakeFiles/pilight-uuid.dir/requires: CMakeFiles/pilight-uuid.dir/uuid.c.o.requires
.PHONY : CMakeFiles/pilight-uuid.dir/requires

CMakeFiles/pilight-uuid.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pilight-uuid.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pilight-uuid.dir/clean

CMakeFiles/pilight-uuid.dir/depend:
	cd /pilight && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /pilight /pilight /pilight /pilight /pilight/CMakeFiles/pilight-uuid.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pilight-uuid.dir/depend

