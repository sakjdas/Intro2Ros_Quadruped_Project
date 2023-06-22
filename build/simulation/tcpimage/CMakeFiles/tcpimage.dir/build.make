# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/simulation

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation

# Include any dependencies generated for this target.
include tcpimage/CMakeFiles/tcpimage.dir/depend.make

# Include the progress variables for this target.
include tcpimage/CMakeFiles/tcpimage.dir/progress.make

# Include the compile flags for this target's objects.
include tcpimage/CMakeFiles/tcpimage.dir/flags.make

tcpimage/CMakeFiles/tcpimage.dir/TCPImageServer.cpp.o: tcpimage/CMakeFiles/tcpimage.dir/flags.make
tcpimage/CMakeFiles/tcpimage.dir/TCPImageServer.cpp.o: /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/simulation/tcpimage/TCPImageServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tcpimage/CMakeFiles/tcpimage.dir/TCPImageServer.cpp.o"
	cd /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/tcpimage && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tcpimage.dir/TCPImageServer.cpp.o -c /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/simulation/tcpimage/TCPImageServer.cpp

tcpimage/CMakeFiles/tcpimage.dir/TCPImageServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tcpimage.dir/TCPImageServer.cpp.i"
	cd /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/tcpimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/simulation/tcpimage/TCPImageServer.cpp > CMakeFiles/tcpimage.dir/TCPImageServer.cpp.i

tcpimage/CMakeFiles/tcpimage.dir/TCPImageServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tcpimage.dir/TCPImageServer.cpp.s"
	cd /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/tcpimage && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/simulation/tcpimage/TCPImageServer.cpp -o CMakeFiles/tcpimage.dir/TCPImageServer.cpp.s

# Object files for target tcpimage
tcpimage_OBJECTS = \
"CMakeFiles/tcpimage.dir/TCPImageServer.cpp.o"

# External object files for target tcpimage
tcpimage_EXTERNAL_OBJECTS =

/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/simulation/lib/libtcpimage.so: tcpimage/CMakeFiles/tcpimage.dir/TCPImageServer.cpp.o
/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/simulation/lib/libtcpimage.so: tcpimage/CMakeFiles/tcpimage.dir/build.make
/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/simulation/lib/libtcpimage.so: /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/simulation/lib/libtcpstreamreader.so
/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/simulation/lib/libtcpimage.so: tcpimage/CMakeFiles/tcpimage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/simulation/lib/libtcpimage.so"
	cd /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/tcpimage && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tcpimage.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tcpimage/CMakeFiles/tcpimage.dir/build: /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/simulation/lib/libtcpimage.so

.PHONY : tcpimage/CMakeFiles/tcpimage.dir/build

tcpimage/CMakeFiles/tcpimage.dir/clean:
	cd /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/tcpimage && $(CMAKE_COMMAND) -P CMakeFiles/tcpimage.dir/cmake_clean.cmake
.PHONY : tcpimage/CMakeFiles/tcpimage.dir/clean

tcpimage/CMakeFiles/tcpimage.dir/depend:
	cd /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/simulation /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/simulation/tcpimage /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/tcpimage /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/tcpimage/CMakeFiles/tcpimage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tcpimage/CMakeFiles/tcpimage.dir/depend
