set(libsocket_INCLUDE_DIRS "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers")

set(libsocket_BINARY_DIR "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket-build")

include(${libsocket_BINARY_DIR}/libsocketTargets.cmake)

set(libsocket_LIBRARIES socket++)
