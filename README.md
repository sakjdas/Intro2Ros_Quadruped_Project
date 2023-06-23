# Intro2Ros_Quadruped_Project
Code of the quadruped final project.

# build the environment
catkin build

# simulation
roslaunch simulation simulation.launch 

#__in one step__
roslaunch controller_pkg mylaunchfile.launch 






#__seperate__
# controller
rosrun controller_pkg controller_node  
or:  
rosrun plumbing_dog pub_com

# depth image to point cloud
rosrun depth2cloud depth2cloud

# transfer point cloud into voxel grid
rosrun depth2cloud pc2voxel

# path planner
# 1. voxel2gridmap
rosrun voxel_mapping voxel2gridmap 
# 2. path planner
rosrun random_tree_planning random_tree_planning 
