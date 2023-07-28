Clone the repository and cd to the folder which contains the source folder.

Before building, run the command below to install some ros packages. open the terminal and run:

------------------------------------------------------------------------------------------------
sudo apt-get install ros-noetic-image-pipeline

sudo apt-get install ros-noetic-octomap

sudo apt-get install ros-noetic-octomap-server

sudo apt-get install ros-noetic-octomap-plugins

sudo apt-get install ros-noetic-move-base

sudo apt-get install ros-noetic-map-server

------------------------------------------------------------------------------------------------

Build the project, run <catkin build> in the terminal.

download the unity file of Quadruped in the following website: https://syncandshare.lrz.de/getlink/fiEg9ocZ6Pc5iuEa4QqN1b/

put the downloaded unity file in devel/lib/simulation/

run source devel/setup.bash

if you want to run test planning algorithm, which we used to test different combination of the 5 robot link parameters, run following command:
rosrun controller_pkg controller_node_direct_run

if you want to run our default planning configuration, run the command below:
roslaunch simulation simulation_rviz.launch 

