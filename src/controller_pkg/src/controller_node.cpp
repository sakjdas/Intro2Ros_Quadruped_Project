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
#include <algorithm>

#define PI M_PI

//define state here

#define CLOCKWISE_TURN 8
#define COUNTERCLOCKWISE_TURN -8
#define UPSTAIR 2
#define SLOPE 3
#define STOP -1


#include <eigen3/Eigen/Dense>

// If you choose to use Eigen, tf provides useful functions to convert tf 
// messages to eigen types and vice versa, have a look to the documentation:
// http://docs.ros.org/melodic/api/eigen_conversions/html/namespacetf.html
#include <eigen_conversions/eigen_msg.h>

class controllerNode{
  ros::NodeHandle nh;


  ros::Subscriber desired_state, current_state;
  ros::Publisher prop_speeds;
  ros::Timer timer;

  // Set the required vectors to 2d

  // Controller internals (you will have to set them below)
  // Current state
  Eigen::Vector2d x;     // current position of the dog's c.o.m. in the world frame
  Eigen::Vector2d v;     // current velocity of the dog's c.o.m. in the world frame
  Eigen::Vector2d v_normalized;  // normalized v 

  // Desired state
  Eigen::Vector2d xd;    // desired position of the dog's c.o.m. in the world frame
  Eigen::Vector2d vd;    // desired velocity of the dog's c.o.m. in the world frame

  
  Eigen::Vector2d distance; // The distance vector from current position to desired position
  Eigen::Vector2d distance_normalized;  // normalized distance
  
  double cos_theta; // The cosine value of the angle between distance and the current velocity
  double scaler_rotate; // The scaler to scale the rotation angle
  double scaler_speed; // The scaler to scale the speed (speed gain)
  double amplitude; // The amplitude of the robot foot
  double scaler_distance2rot; // The scaler describing the effect of distance on rotational speed
  double base_rotate;
  double w;
  int state;

  double hz;             // frequency of the main control loop

public:
  // controllerNode类的构造函数的定义
  // 初始化列表将成员变量hz设置为1000.0
  controllerNode():hz(1000.0),state(0){
    desired_state = nh.subscribe("desired_state", 1, &controllerNode::onDesiredState, this);
    current_state = nh.subscribe("current_state_est", 1, &controllerNode::onCurrentState, this);
    prop_speeds = nh.advertise<mav_msgs::Actuators>("commands", 1);
    // in a time period the controlLoop will be called
    // 创建一个定时器，用于定期触发controlLoop成员函数
    timer = nh.createTimer(ros::Rate(hz), &controllerNode::controlLoop, this);
  }

  void onDesiredState(const trajectory_msgs::MultiDOFJointTrajectoryPoint& des_state){
    // Position
    // MultiDOFJointTrajectoryPoint, 通常只使用数组中的第一个元素，因为它描述了一个特定时间点的状态
    // des_state.transforms是一个变换的数组，通过[0]选择第一个变换，然后从该变换中提取位置信息。
    geometry_msgs::Vector3 t = des_state.transforms[0].translation;
    // get desired position
    xd << t.x, t.y;
    // ???
    state = std::floor(t.z); //note the 3rd term is state
  }

  void onCurrentState(const nav_msgs::Odometry& cur_state){
    // 从cur_state中提取机器人当前位置和速度信息。通过cur_state.pose.pose.position.x和cur_state.pose.pose.position.y获取机器人在x和y方向上的位置。通过cur_state.twist.twist.linear.x和cur_state.twist.twist.linear.y获取机器人在x和y方向上的线速度。  
    // x is position information
    // v is linear velocity information
    x << cur_state.pose.pose.position.x,cur_state.pose.pose.position.y;
    v << cur_state.twist.twist.linear.x,cur_state.twist.twist.linear.y;
    
    // compute the 2d distance
    distance = xd - x;

    // set the speed gain to control the magnitude of the robot speed
    // 限制速度增益在0.2到1.0之间
    scaler_speed = std::min(8*std::sqrt(distance.dot(distance)), 1.0);
    scaler_speed = std::max(scaler_speed, 0.2);

    // stop moving if the robot is close enough to the target point
    if(std::sqrt(distance.dot(distance)) < 1e-2){
      scaler_speed = 0.0;
    }

    // the scaler that describes the effect of distance on rotational speed
    scaler_distance2rot = std::min(4*distance.dot(distance),3.0) + 
      0.05 / (distance.dot(distance) + 0.01);


    // compute cos_theta with dot product of distance_normalized and v_normalized
    // define also scaler_rotate
    // rotate only if v and distance are non-zero vectors
    // 仅当速度和距离都是非零向量时，计算cos_theta，即距离向量归一化(distance_normalized)与速度向量归一化(v_normalized)的点积的绝对值。同时，根据叉积的正负来确定旋转方向。如果叉积为非正数，则将scaler_rotate设置为4.0 + scaler_distance2rot，否则设置为-4.0 - scaler_distance2rot。如果distance_normalized.dot(v_normalized)小于0.8，则将cos_theta设置为0.3，scaler_speed设置为0.1，以便在目标点在机器人后方或角度过大时进行快速旋转。
    if (std::sqrt(v.dot(v)) && std::sqrt(distance.dot(distance))){
      // normalize distance and v
      distance_normalized = distance / std::sqrt(distance.dot(distance));
      v_normalized = v / std::sqrt(v.dot(v));
      cos_theta = std::abs(distance_normalized.dot(v_normalized));
      // use cross product to difine the rotation direction
      if(v_normalized({0})*distance_normalized({1}) - v_normalized({1})*distance_normalized({0})<=0){
        scaler_rotate = 4.0 + scaler_distance2rot;
      }
      else{
        scaler_rotate = - 4.0 - scaler_distance2rot;
      }
      // when theta is too large or the target point is behind the robot, we need a faster rotation.
      // turning fast if target point is behind the robot or theta is too large
      if(distance_normalized.dot(v_normalized) < 0.8){
        cos_theta = 0.3;
        scaler_speed = 0.1;
      }

    }
    // if v or distance is zero vector, stop rotating
    else{
      scaler_rotate = 0.0;
      cos_theta = 1.0;
    }
    // ROS_INFO_NAMED("onCurrentState", "x:%f y:%f s:%f a:%f", x({0}), x({1}), std::sqrt(distance.dot(distance)), amplitude);
  }


  void controlLoop(const ros::TimerEvent& t){

    mav_msgs::Actuators msg;
    msg.angular_velocities.resize(5);
    switch(state){
      case CLOCKWISE_TURN:  //Turn clockwise
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 45; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 7; // Frequency of legs 
        break;

      case COUNTERCLOCKWISE_TURN: //Turn counterclockwise
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = -45; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 7; // Frequency of legs 
        break;

      case UPSTAIR:
        msg.angular_velocities[0] = -1.0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 0; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 1.4; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 7; // Frequency of legs 
        break;

      case SLOPE:
        msg.angular_velocities[0] = 1.0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 0; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 1.2; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 7; // Frequency of legs 
        break;

      case STOP:
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 0; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 0; // Frequency of legs 
        break;
        
      default:
        msg.angular_velocities[0] = 0; // Phase between front and back legs (in degree)
        msg.angular_velocities[1] = 90; // Phase between front left + back right legs and front right and left back legs
        msg.angular_velocities[2] = 0; // Amplitude change of all legs
        msg.angular_velocities[3] = 0; // Amplitude change of back legs (added to angular_velocities[2])
        msg.angular_velocities[4] = 7; // Frequency of legs
    } 
    prop_speeds.publish(msg);
  }
};


int main(int argc, char** argv){
  ros::init(argc, argv, "controller_node");
  ROS_INFO_NAMED("controller", "Controller started!");
  controllerNode n;
  ros::spin();
}
