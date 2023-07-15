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

#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseArray.h>
#include <sstream>

#define PI M_PI

#define kp 2.58
#define kd 0.47
#define ks 0


#include <eigen3/Eigen/Dense>

// If you choose to use Eigen, tf provides useful functions to convert tf 
// messages to eigen types and vice versa, have a look to the documentation:
// http://docs.ros.org/melodic/api/eigen_conversions/html/namespacetf.html
#include <eigen_conversions/eigen_msg.h>

class controllerNode{
  ros::NodeHandle nh;

  ros::Subscriber desired_state, current_state, des_pos;
  ros::Publisher commands;
  ros::Timer timer;
  std::stringstream ss;

  // Controller internals (you will have to set them below)
  // Current state
  Eigen::Vector3d x;     // current position of the UAV's c.o.m. in the world frame
  Eigen::Vector3d v;     // current velocity of the UAV's c.o.m. in the world frame
  Eigen::Matrix3d R;     // current orientation of the UAV
  Eigen::Vector3d omega; // current angular velocity of the UAV's c.o.m. in the *body* frame

  // Desired state
  Eigen::Vector3d xd;    // desired position of the UAV's c.o.m. in the world frame
  Eigen::Vector3d vd;    // desired velocity of the UAV's c.o.m. in the world frame
  Eigen::Vector3d ad;    // desired acceleration of the UAV's c.o.m. in the world frame
  double yawd;           // desired yaw angle

  double hz;             // frequency of the main control loop

  // newly define 
  double position_error = 0;
  double previous__position_error = 0;
  double angle_error = 0;
  double previous__angle_error = 0;
  double sumdistance = 0;
  double sumangle = 0;
  double roll = 0;
  double pitch = 0;
  double yaw = 0;
  // loop 
  int i = 0;

public:
  controllerNode():hz(2){
      
      desired_state = nh.subscribe("desired_state", 1, &controllerNode::onDesiredState, this);
      current_state = nh.subscribe("current_state_est", 1, &controllerNode::onCurrentState, this);

      commands = nh.advertise<mav_msgs::Actuators>("commands", 1);
      timer = nh.createTimer(ros::Rate(hz), &controllerNode::controlLoop, this);
  }

  void onDesiredState(const trajectory_msgs::MultiDOFJointTrajectoryPoint& des_state){
      
      // Position
      geometry_msgs::Vector3 t = des_state.transforms[0].translation;
      xd << t.x, t.y, t.z;

      // Velocities
      geometry_msgs::Vector3 v = des_state.velocities[0].linear;
      vd << v.x, v.y, v.z;

      // Accelerations
      geometry_msgs::Vector3 a = des_state.accelerations[0].linear;
      ad << a.x, a.y, a.z;
      
      tf::Quaternion q;
      tf::quaternionMsgToTF(des_state.transforms[0].rotation , q);
      yawd = tf::getYaw(q);
  }

  void onCurrentState(const nav_msgs::Odometry& cur_state){
      
    x << cur_state.pose.pose.position.x,cur_state.pose.pose.position.y,cur_state.pose.pose.position.z;
    v << cur_state.twist.twist.linear.x,cur_state.twist.twist.linear.y,cur_state.twist.twist.linear.z;
    omega << cur_state.twist.twist.angular.x,cur_state.twist.twist.angular.y,cur_state.twist.twist.angular.z;
    Eigen::Quaterniond q;
    tf::quaternionMsgToEigen (cur_state.pose.pose.orientation, q);
    tf::Quaternion quat;
    tf::quaternionMsgToTF(cur_state.pose.pose.orientation, quat);
    tf::Matrix3x3(quat).getRPY(roll,pitch,yaw);
    R = q.toRotationMatrix();

    // Rotate omega
    omega = R.transpose()*omega;
  }

 


  void controlLoop(const ros::TimerEvent& t){

    mav_msgs::Actuators msg;
    msg.angular_velocities.resize(5);
    if(i<=68)
    {
      // -45 0 20 30 7
      //45 0 20 20 7
      // 45 0 30 20 7 two times quickly
      // 45 0 40 20 7
      // 90 0 0 20 5 jump
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 90; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=110)
    {
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 45; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=195)
    {
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 90; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=215)
    {
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 45; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=256)
    {
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 90; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=272)
    {
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = -45; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=317)
    {
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 90; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=359)
    {
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = -45; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=900)
    {
    // step 0 90 25 -10 7
    // 90 0 40 -10 2
    msg.angular_velocities[0] = 45; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 0; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 40; // Amplitude change of all legs
    msg.angular_velocities[3] = 20; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }

    else if (i<=1500)
    {
    // slop
    msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
    msg.angular_velocities[1] = 90; // Phase between front left + back right legs and front right and left back legs
    msg.angular_velocities[2] = 0; // Amplitude change of all legs
    msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
    msg.angular_velocities[4] = 7; // Frequency of legs
    }


    ROS_INFO("loop value: %d", i);

    commands.publish(msg);
    i++;
  }
};

int main(int argc, char** argv){
  ros::init(argc, argv, "controller_node_test");
  ROS_INFO_NAMED("controller", "Controller started!");
  controllerNode n;
  ros::spin();
}
