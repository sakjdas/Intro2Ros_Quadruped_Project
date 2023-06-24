#include <ros/ros.h>

#include <ros/console.h>

#include <tf/transform_datatypes.h>
#include <tf_conversions/tf_eigen.h>
#include <eigen_conversions/eigen_msg.h>
#include <mav_msgs/Actuators.h>
#include <nav_msgs/Odometry.h>
#include <trajectory_msgs/MultiDOFJointTrajectoryPoint.h>
#include <math.h>
#include <std_msgs/Float64.h>

#define PI M_PI


#include <eigen3/Eigen/Dense>

// If you choose to use Eigen, tf provides useful functions to convert tf 
// messages to eigen types and vice versa, have a look to the documentation:
// http://docs.ros.org/melodic/api/eigen_conversions/html/namespacetf.html
#include <eigen_conversions/eigen_msg.h>

class controllerNode{
  ros::NodeHandle nh;

  ros::Publisher commands;
  ros::Timer timer;


  // Controller internals (you will have to set them below)
  // Current state
  // ***  current position, velocity, rotation and angular velocity
  Eigen::Vector3d x;     // current position of the UAV's c.o.m. in the world frame
  Eigen::Vector3d v;     // current velocity of the UAV's c.o.m. in the world frame
  Eigen::Matrix3d R;     // current orientation of the UAV
  Eigen::Vector3d omega; // current angular velocity of the UAV's c.o.m. in the *body* frame

  // Desired state
  // ***  desired position, velocity, rotation and angular velocity
  Eigen::Vector3d xd;    // desired position of the UAV's c.o.m. in the world frame
  Eigen::Vector3d vd;    // desired velocity of the UAV's c.o.m. in the world frame
  Eigen::Vector3d ad;    // desired acceleration of the UAV's c.o.m. in the world frame
  double yawd;           // desired yaw angle

  double hz;             // frequency of the main control loop

public:
  // *** controllerNode类的构造函数。在这里，它初始化了ROS节点句柄、发布器和定时器，并将控制循环的频率设置为1000Hz
  controllerNode():hz(1000.0){
      // *** 创建了一个名为commands的发布器，用于发布mav_msgs::Actuators类型的消息, commands is the topic we send the messages, 1 means if new data comes in,
      // we will remove the orrgin data and preserve the current data.
      commands = nh.advertise<mav_msgs::Actuators>("commands", 1);
      timer = nh.createTimer(ros::Rate(hz), &controllerNode::controlLoop, this);
  }



  void controlLoop(const ros::TimerEvent& t){

    mav_msgs::Actuators msg;

    msg.angular_velocities.resize(5);
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 90; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs

    commands.publish(msg);

  }
};

int main(int argc, char** argv){
  // *** 初始化ROS节点，设置节点名称为"controller_node"
  ros::init(argc, argv, "controller_node");
  ROS_INFO_NAMED("controller", "Controller started!");
  // *** 创建了一个controllerNode对象n
  controllerNode n;
  // *** 通过ros::spin()进入ROS系统的循环等待状态，等待接收和处理消息
  ros::spin();
}
