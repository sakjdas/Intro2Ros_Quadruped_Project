# simulation and rviz
roslaunch simulation simulation_rviz.launch 
# run test planning
rosrun controller_pkg controller_node_direct_run
# run default planning
roslaunch controller_pkg planning

