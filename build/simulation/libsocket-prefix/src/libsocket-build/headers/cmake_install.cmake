# Install script for directory: /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/simulation")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/libsocket" TYPE FILE FILES
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./unixdgram.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./exception.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./inetclientdgram.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./libinetsocket.h"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./unixserverstream.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./dgramclient.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./streamclient.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./inetserverstream.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./unixclientdgram.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./socket.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./inetbase.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./inetserverdgram.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./unixclientstream.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./libunixsocket.h"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./select.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./inetclientstream.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./unixbase.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./unixserverdgram.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./inetdgram.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./dgramoverstream.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./framing.hpp"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers/./epoll.hpp"
    )
endif()

