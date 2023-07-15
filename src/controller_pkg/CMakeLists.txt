cmake_minimum_required(VERSION 2.8.3)
project(controller_pkg)

include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wl,--no-as-needed")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
endif()

find_package(catkin REQUIRED COMPONENTS 
  roscpp 
  rospy 
  std_msgs 
  geometry_msgs 
  mav_msgs
  eigen_conversions
  tf_conversions
  state_indicator_msgs
)

catkin_package(CATKIN_DEPENDS 
  roscpp 
  std_msgs 
  mav_msgs 
  tf
  eigen_conversions
  tf_conversions
  state_indicator_msgs
)

find_package(Eigen3)

include_directories(${catkin_INCLUDE_DIRS})
add_executable(controller_node src/controller_node.cpp)
add_dependencies(controller_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(controller_node ${catkin_LIBRARIES})

add_executable(trajectory_node src/trajectory_node.cpp)
add_dependencies(trajectory_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(trajectory_node ${catkin_LIBRARIES})

add_executable(state_machine_node src/state_machine_node.cpp)
add_dependencies(state_machine_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(state_machine_node ${catkin_LIBRARIES})

add_executable(controller_node_direct_run src/controller_node_direct_run.cpp)
add_dependencies(controller_node_direct_run ${catkin_EXPORTED_TARGETS})
target_link_libraries(controller_node_direct_run ${catkin_LIBRARIES})

SET(CMAKE_BUILD_TYPE "Debug")  
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
