# CMake generated Testfile for 
# Source directory: /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/utilities/fla_utils
# Build directory: /home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/fla_utils
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_fla_utils_gtest_fla_utils_test "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/fla_utils/catkin_generated/env_cached.sh" "/usr/bin/python3" "/opt/ros/noetic/share/catkin/cmake/test/run_tests.py" "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/fla_utils/test_results/fla_utils/gtest-fla_utils_test.xml" "--return-code" "/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/devel/.private/fla_utils/lib/fla_utils/fla_utils_test --gtest_output=xml:/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/build/fla_utils/test_results/fla_utils/gtest-fla_utils_test.xml")
set_tests_properties(_ctest_fla_utils_gtest_fla_utils_test PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/noetic/share/catkin/cmake/test/tests.cmake;160;add_test;/opt/ros/noetic/share/catkin/cmake/test/gtest.cmake;98;catkin_run_tests_target;/opt/ros/noetic/share/catkin/cmake/test/gtest.cmake;37;_catkin_add_google_test;/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/utilities/fla_utils/CMakeLists.txt;52;catkin_add_gtest;/home/hanyu/ROS_project/Intro2Ros_Quadruped_Project/src/utilities/fla_utils/CMakeLists.txt;0;")
subdirs("gtest")
