# Intro2Ros_Quadruped_Project
Code of the quadruped final project.

# build the environment
catkin build

# simulation
roslaunch simulation simulation.launch 

# controller
rosrun controller_pkg controller_node
or:
rosrun plumbing_dog pub_com

# depth image to point cloud
rosrun depth2cloud depth2cloud_node

# transfer point cloud into voxel grid
rosrun depth2cloud pc2voxel

# path planner
