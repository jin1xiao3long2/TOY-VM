# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = D:\JetBrians\apps\CLion\ch-0\212.4746.93\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = D:\JetBrians\apps\CLion\ch-0\212.4746.93\bin\cmake\win\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\mywork\testvm\vm

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\mywork\testvm\vm\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/csvm.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/csvm.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/csvm.dir/flags.make

CMakeFiles/csvm.dir/main.cpp.obj: CMakeFiles/csvm.dir/flags.make
CMakeFiles/csvm.dir/main.cpp.obj: CMakeFiles/csvm.dir/includes_CXX.rsp
CMakeFiles/csvm.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\mywork\testvm\vm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/csvm.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\csvm.dir\main.cpp.obj -c D:\mywork\testvm\vm\main.cpp

CMakeFiles/csvm.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/csvm.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\mywork\testvm\vm\main.cpp > CMakeFiles\csvm.dir\main.cpp.i

CMakeFiles/csvm.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/csvm.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\mywork\testvm\vm\main.cpp -o CMakeFiles\csvm.dir\main.cpp.s

# Object files for target csvm
csvm_OBJECTS = \
"CMakeFiles/csvm.dir/main.cpp.obj"

# External object files for target csvm
csvm_EXTERNAL_OBJECTS =

csvm.exe: CMakeFiles/csvm.dir/main.cpp.obj
csvm.exe: CMakeFiles/csvm.dir/build.make
csvm.exe: CMakeFiles/csvm.dir/linklibs.rsp
csvm.exe: CMakeFiles/csvm.dir/objects1.rsp
csvm.exe: CMakeFiles/csvm.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\mywork\testvm\vm\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable csvm.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\csvm.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/csvm.dir/build: csvm.exe
.PHONY : CMakeFiles/csvm.dir/build

CMakeFiles/csvm.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\csvm.dir\cmake_clean.cmake
.PHONY : CMakeFiles/csvm.dir/clean

CMakeFiles/csvm.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\mywork\testvm\vm D:\mywork\testvm\vm D:\mywork\testvm\vm\cmake-build-debug D:\mywork\testvm\vm\cmake-build-debug D:\mywork\testvm\vm\cmake-build-debug\CMakeFiles\csvm.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/csvm.dir/depend

