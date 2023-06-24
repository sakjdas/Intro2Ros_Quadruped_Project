set(libsocket_INCLUDE_DIRS "/home/hao-guo/Intro2Ros2023_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket/headers")

set(libsocket_BINARY_DIR "/home/hao-guo/Intro2Ros2023_Quadruped_Project/build/simulation/libsocket-prefix/src/libsocket-build")

include(${libsocket_BINARY_DIR}/libsocketTargets.cmake)

set(libsocket_LIBRARIES socket++)
