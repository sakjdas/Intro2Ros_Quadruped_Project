#include <ros/ros.h>

#include <ros/console.h>

#include <tf/transform_datatypes.h>
#include <tf_conversions/tf_eigen.h>
#include <eigen_conversions/eigen_msg.h>
#include <mav_msgs/Actuators.h>
#include <nav_msgs/Odometry.h>
#include <trajectory_msgs/MultiDOFJointTrajectoryPoint.h>
#include <math.h>
#include <std_msgs/Int32.h>
#include <algorithm>

#define PI M_PI

//state definition
#define INITIAL 0
#define FORWARD 1
#define CLOCKWISE_ROTATE 2
#define COUNTERCLOCKWISE_ROTATE 3
#define JUMP 4
#define END 5


#include <eigen3/Eigen/Dense>

#include <state_indicator_msgs/state_indicator.h>

// If you choose to use Eigen, tf provides useful functions to convert tf 
// messages to eigen types and vice versa, have a look to the documentation:
// http://docs.ros.org/melodic/api/eigen_conversions/html/namespacetf.html
#include <eigen_conversions/eigen_msg.h>

class controllerNode{
  ros::NodeHandle nh;
  ros::Subscriber state_sub;   //subscribe to state from state machine
  ros::Timer timer;
  ros::Publisher commands;  //publish commands

  state_indicator_msgs::state_indicator state;
  double hz;             // frequency of the main control loop

public:
  controllerNode():hz(1000.0){
    state_sub = nh.subscribe("state", 1, &controllerNode::onState, this);
    commands  = nh.advertise<mav_msgs::Actuators>("commands", 1);
    // in a time period the controlLoop will be called
    timer = nh.createTimer(ros::Rate(hz), &controllerNode::controlLoop, this);
    state.state_msg = INITIAL;
  }

  void onState(const state_indicator_msgs::state_indicator& cur_state){
      state.state_msg = cur_state.state_msg;
  }


  void controlLoop(const ros::TimerEvent& t){

    mav_msgs::Actuators msg;
    msg.angular_velocities.resize(5);
    switch(state.state_msg){
      case CLOCKWISE_ROTATE:  //Turn clockwise
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 45; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 7; // Frequency of legs
        break;

      case COUNTERCLOCKWISE_ROTATE: //Turn counterclockwise
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = -45; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 7; // Frequency of legs
        break;

      case JUMP:
        msg.angular_velocities[0] = 90; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 0; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 20; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 0; // Frequency of legs
        break;

      case INITIAL:
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 0; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 0; // Frequency of legs
        break;

      case END:
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 0; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 0; // Frequency of legs
        break;

      case FORWARD:
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 90; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 8; // Frequency of legs
        break;
      
      default:
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 0; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 0; // Frequency of legs
    } 
    commands.publish(msg);
  }
};


int main(int argc, char** argv){
  ros::init(argc, argv, "controller_node");
  ROS_INFO_NAMED("controller", "Controller started!");
  controllerNode n;
  ros::spin();
}
