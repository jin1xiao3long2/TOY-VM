# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.19

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\JetBrians\apps\CLion\ch-0\211.7628.27\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = D:\JetBrians\apps\CLion\ch-0\211.7628.27\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\mywork\testvm\vm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\mywork\testvm\vm\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/rvm.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/rvm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/rvm.dir/flags.make

CMakeFiles/rvm.dir/main.cpp.obj: CMakeFiles/rvm.dir/flags.make
CMakeFiles/rvm.dir/main.cpp.obj: CMakeFiles/rvm.dir/includes_CXX.rsp
CMakeFiles/rvm.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\mywork\testvm\vm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/rvm.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\rvm.dir\main.cpp.obj -c D:\mywork\testvm\vm\main.cpp

CMakeFiles/rvm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/rvm.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\mywork\testvm\vm\main.cpp > CMakeFiles\rvm.dir\main.cpp.i

CMakeFiles/rvm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/rvm.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\mywork\testvm\vm\main.cpp -o CMakeFiles\rvm.dir\main.cpp.s

# Object files for target rvm
rvm_OBJECTS = \
"CMakeFiles/rvm.dir/main.cpp.obj"

# External object files for target rvm
rvm_EXTERNAL_OBJECTS =

rvm.exe: CMakeFiles/rvm.dir/main.cpp.obj
rvm.exe: CMakeFiles/rvm.dir/build.make
rvm.exe: CMakeFiles/rvm.dir/linklibs.rsp
rvm.exe: CMakeFiles/rvm.dir/objects1.rsp
rvm.exe: CMakeFiles/rvm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\mywork\testvm\vm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable rvm.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\rvm.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/rvm.dir/build: rvm.exe

.PHONY : CMakeFiles/rvm.dir/build

CMakeFiles/rvm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\rvm.dir\cmake_clean.cmake
.PHONY : CMakeFiles/rvm.dir/clean

CMakeFiles/rvm.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\mywork\testvm\vm D:\mywork\testvm\vm D:\mywork\testvm\vm\cmake-build-debug D:\mywork\testvm\vm\cmake-build-debug D:\mywork\testvm\vm\cmake-build-debug\CMakeFiles\rvm.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/rvm.dir/depend

