# Install script for directory: /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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
  
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
        file(MAKE_DIRECTORY "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}")
      endif()
      if (NOT EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin")
        file(WRITE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/.catkin" "")
      endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/_setup_util.py")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install" TYPE PROGRAM FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/_setup_util.py")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/env.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install" TYPE PROGRAM FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/env.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/setup.bash;/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/local_setup.bash")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install" TYPE FILE FILES
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/setup.bash"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/local_setup.bash"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/setup.sh;/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/local_setup.sh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install" TYPE FILE FILES
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/setup.sh"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/local_setup.sh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/setup.zsh;/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/local_setup.zsh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install" TYPE FILE FILES
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/setup.zsh"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/local_setup.zsh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install/.rosinstall")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/install" TYPE FILE FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/.rosinstall")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nav_msgs/msg" TYPE FILE FILES
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/msg/GridCells.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/msg/MapMetaData.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/msg/OccupancyGrid.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/msg/Odometry.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/msg/Path.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nav_msgs/srv" TYPE FILE FILES
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/srv/GetMap.srv"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/srv/GetPlan.srv"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/srv/SetMap.srv"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/srv/LoadMap.srv"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nav_msgs/action" TYPE FILE FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/action/GetMap.action")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nav_msgs/msg" TYPE FILE FILES
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/nav_msgs/msg/GetMapAction.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/nav_msgs/msg/GetMapActionGoal.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/nav_msgs/msg/GetMapActionResult.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/nav_msgs/msg/GetMapActionFeedback.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/nav_msgs/msg/GetMapGoal.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/nav_msgs/msg/GetMapResult.msg"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/nav_msgs/msg/GetMapFeedback.msg"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nav_msgs/cmake" TYPE FILE FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/nav_msgs-msg-paths.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE DIRECTORY FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/include/nav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/roseus/ros" TYPE DIRECTORY FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/roseus/ros/nav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/common-lisp/ros" TYPE DIRECTORY FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/common-lisp/ros/nav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/gennodejs/ros" TYPE DIRECTORY FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/share/gennodejs/ros/nav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  execute_process(COMMAND "/usr/bin/python3" -m compileall "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/lib/python3/dist-packages/nav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/python3/dist-packages" TYPE DIRECTORY FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/nav_msgs/lib/python3/dist-packages/nav_msgs")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/nav_msgs.pc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nav_msgs/cmake" TYPE FILE FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/nav_msgs-msg-extras.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nav_msgs/cmake" TYPE FILE FILES
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/nav_msgsConfig.cmake"
    "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/catkin_generated/installspace/nav_msgsConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/nav_msgs" TYPE FILE FILES "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/nav_msgs/package.xml")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/gtest/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/nav_msgs/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
