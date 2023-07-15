//Author: Dian Yuan
//Comments:
//16.07.2022 Simple position and velocity publisher
//29.07.2022 trajectory visualization

#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <eigen3/Eigen/Dense>
#include <trajectory_msgs/MultiDOFJointTrajectoryPoint.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

class traj_publisher{
  ros::NodeHandle nh;
  ros::Publisher traj_vis_pub, current_goal_pub; 
  ros::Subscriber path_point_sub, position_sub;
  ros::Timer timer; 

  double hz; //frequency of trajectory publishing

  geometry_msgs::Point path_point;
  visualization_msgs::Marker traj, current_goal; //Marker in rviz

public:
  traj_publisher():hz(50.0){
  
    path_point_sub = nh.subscribe("path_point",1,&traj_publisher::GetPathPoint,this);
    position_sub = nh.subscribe("current_state_est", 100, &traj_publisher::getTraj, this);

    traj_vis_pub = nh.advertise<visualization_msgs::Marker>("traj_marker",100);
    current_goal_pub = nh.advertise<visualization_msgs::Marker>("current_goal",1);

    timer = nh.createTimer(ros::Rate(hz), &traj_publisher::traj_pub_Loop, this);

    traj.header.frame_id = current_goal.header.frame_id = "world";
    traj.header.stamp = ros::Time::now();
    traj.ns = current_goal.ns = "traj_publisher";
    traj.id = 33;
    traj.action = visualization_msgs::Marker::ADD;
    traj.pose.orientation.w = 1.0;
    traj.type = visualization_msgs::Marker::LINE_STRIP;
    traj.scale.x = traj.scale.y = traj.scale.z = 0.04;
    traj.color.r = 0.99;
    traj.color.g = 0.65;
    traj.color.a = 0.88;
    traj.lifetime = ros::Duration();

    current_goal.id = 66;
    current_goal.action = visualization_msgs::Marker::ADD;
    current_goal.scale.x = current_goal.scale.y = current_goal.scale.z = 0.08;
    current_goal.color.r = current_goal.color.a = 1.0;
    current_goal.type = visualization_msgs::Marker::CUBE;
    current_goal.lifetime = ros::Duration(1/hz);

  }

  //get path point from planning node
  void GetPathPoint(const geometry_msgs::Point& path){
      path_point = path;
  }

  void getTraj(const nav_msgs::Odometry& cur_state){
    geometry_msgs::Point p;
    p.x = cur_state.pose.pose.position.x;
    p.y = cur_state.pose.pose.position.y;
    p.z = 0;
    traj.points.push_back(p);
  }


 
  void traj_pub_Loop(const ros::TimerEvent& t){
    current_goal.header.stamp = ros::Time();
    current_goal.pose.position.x = path_point.x;
    current_goal.pose.position.y = path_point.y;
    current_goal.pose.position.z = 0;
    current_goal.pose.orientation.w = 1.0;

    traj_vis_pub.publish(traj);
    current_goal_pub.publish(current_goal);
  }
};

int main(int argc, char** argv){
  ros::init(argc, argv, "traj_publisher");
  traj_publisher n;
  ros::spin();
  return 0;
}
