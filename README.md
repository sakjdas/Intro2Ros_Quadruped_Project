Ubuntu Version: 20.04

Run git clone git@github.com:sakjdas/Intro2Ros_Quadruped_Project.git to clone the repository

Before building, run the command below to install some ros packages. open the terminal and run:

------------------------------------------------------------------------------------------------
sudo apt-get install ros-noetic-image-pipeline

sudo apt-get install ros-noetic-octomap

sudo apt-get install ros-noetic-octomap-server

sudo apt-get install ros-noetic-octomap-plugins

sudo apt-get install ros-noetic-move-base

sudo apt-get install ros-noetic-map-server

------------------------------------------------------------------------------------------------

Cd into the folder which contains the source folder.

Build the project, run <catkin build> in the terminal.

Download the unity file of Quadruped in the following website: https://syncandshare.lrz.de/getlink/fiEg9ocZ6Pc5iuEa4QqN1b/

put the downloaded unity file in devel/lib/simulation/

run source devel/setup.bash

we have two differnent cases, so we still need two terminals

step1: 
run the following command in the first terminal to start the simulation environment, perception pipeline and the visualization tool rviz:
------------------------------------------------------------------------------------------------
roslaunch simulation simulation_rviz.launch

------------------------------------------------------------------------------------------------

step2(choose one of the command below):

open a second terminal and run source devel/setup.bash

if you want to run our planning configuration, run the command below:
------------------------------------------------------------------------------------------------
roslaunch controller_pkg planning.launch
------------------------------------------------------------------------------------------------
if you want to run motion test, which we used to test different combination of the 5 robot link parameters, run following command:
------------------------------------------------------------------------------------------------
rosrun controller_pkg controller_node_direct_run
------------------------------------------------------------------------------------------------

