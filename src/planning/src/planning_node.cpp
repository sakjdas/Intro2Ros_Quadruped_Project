/*
The main function of this node is to publish the next target point of the robot. It will publish a waypoint with geometry_msgs::Point datatype in topic next_waypoint.

waypoint.x, waypoint.y: the coordinates in 2D space;
waypoint.z: the state variable given to the controller;

It can detect if there is a slope/step in front from the occupancy map information and send different state to controller. 

Besides, this node will also publish the destination once this node is initialized.

For more detail about this node, please refer to our documentation.
*/

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <vector>
#include <eigen3/Eigen/Dense>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/OccupancyGrid.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Vector3.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_datatypes.h>
#include <tf/LinearMath/Matrix3x3.h>

#define PI M_PI

class planning_node{
    ros::NodeHandle nh;
    ros::Subscriber robot_pos;  //subscribe to current pose
    ros::Subscriber path_sub;   //subscribe to path from move base  
    ros::Subscriber map_sub;    //subscribe to projected_map with steps

    ros::Publisher path_point_pub;  //publish selected path point

    Eigen::Vector2d current_position;
    Eigen::Vector2d current_velocity;
    Eigen::Vector2d current_direction;

    geometry_msgs::Point path_point;
    double hz;  //frequency of the path point publishing
    ros::Timer timer;

    //parameters used to check if there is step in front of robot
    int map_width;
    int map_height;
    double resolution;
    double origin_x;
    double origin_y;
    int occupancy;
    int occupied_count;
    int idx;

public:
    planning_node():hz(50){
        robot_pos = nh.subscribe("current_state_est", 100, &planning_node::GetPose, this);
        path_sub = nh.subscribe("/move_base_Quadruped/NavfnROS/plan",100,&planning_node::GetPathPoint,this);
        map_sub = nh.subscribe("projected_map_step", 1, &planning_node::CheckStep, this);
      
        path_point_pub = nh.advertise<geometry_msgs::Point>("path_point",1);
        path_point.z = 0;

        timer = nh.createTimer(ros::Rate(hz), &planning_node::PathPointPub, this);

        ROS_INFO("planning_node start");
    }
    
    //get the current position, velocity and orientation
    void GetPose(const nav_msgs::Odometry& cur_state) {
        current_position << cur_state.pose.pose.position.x, cur_state.pose.pose.position.y;
        current_velocity << cur_state.twist.twist.linear.x,cur_state.twist.twist.linear.y;

        // Extract the face direction (yaw angle) from the quaternion orientation
        geometry_msgs::Quaternion orientation = cur_state.pose.pose.orientation;
        double yaw = tf::getYaw(orientation);
        // Calculate the 2D vector based on the yaw angle
        current_direction(0) = cos(yaw);
        current_direction(1) = sin(yaw);
    }

    //get path from global planner
    // !!!!!!
    void GetPathPoint(const nav_msgs::Path& path_info){
        Eigen::Vector2d point;
        Eigen::Vector2d d;
        int i;
        for(i=0; i<path_info.poses.size();i++){
            point<<path_info.poses[i].pose.position.x, path_info.poses[i].pose.position.y;
            d = (point - current_position);
            
            // constraint on distance between robot and path point
            if(d.norm() > 0.5 && d.norm() < 1.0){
                double cos_d2v;
                
                // ensure the path point is in front of robot
                // this condition always true ?? see whether it get the goal. if it is true, only if d == 0.  ??
                if(current_direction.norm() * d.norm() != 0)
                    // 计算当前机器人朝向向量与距离向量之间的夹角的余弦值，使用点乘和向量的模长计算 a * b / (|a| *|b|)
                    cos_d2v = current_direction.dot(d) / (current_direction.norm() * d.norm());
                else
                    cos_d2v = 0;
                if(cos_d2v > -std::sqrt(3)/2){
                    path_point.x = point(0);
                    path_point.y = point(1);
                    break;
                }
            }
            // 如果遍历完所有的路径点后仍未找到满足约束条件的路径点，将当前机器人位置沿着当前朝向方向稍微偏移一点（0.01个单位）作为 path_point
            if(i == path_info.poses.size()-1){
                path_point.x = current_position(0) + 0.01*current_direction(0);
                path_point.y = current_position(1)+ 0.01*current_direction(1);
            }
        }
    }

    // check if there is step or slope in front
    void CheckStep(const nav_msgs::OccupancyGrid& map_info){  
 
        map_width = map_info.info.width;
        map_height = map_info.info.height;
        resolution = map_info.info.resolution;
        origin_x = map_info.info.origin.position.x;
        origin_y = map_info.info.origin.position.y;
        // 初始化 occupied_count 变量为 0，用于记录占用的数量。
        occupied_count= 0;
        // 根据当前目标路径点的坐标，计算其在地图中对应的网格索引（行和列）。这是通过将目标路径点的坐标与地图的原点和分辨率进行计算得到的
        int columns, rows;
            columns = (int) ((path_point.x - origin_x) / resolution);
            rows = (int) ((path_point.y- origin_y) / resolution);
        // 使用嵌套循环遍历目标路径点周围的一个 5x5 的网格范围
        for(int i=-2;i<=2;i++){
            for(int j=-2;j<=2;j++){
                // 根据当前遍历的网格索引，计算在一维数组中对应的索引值，并将其存储在 idx 变量中
                idx = (rows + i) * map_width + columns + j;
                // 从地图数据中获取对应索引位置的占用情况值（occupancy），这个值可能是一个整数，通常表示该网格的占用状态
                occupancy = map_info.data[idx];
                if(occupancy == 100){
                    occupied_count = occupied_count + 1;
                }
            }
        }

        if(occupied_count > 18){
            path_point.z = 2;
            ROS_WARN("There is a step");
        }
        else
            path_point.z = 0;
        
    } 

    void PathPointPub(const ros::TimerEvent& t){
        path_point_pub.publish(path_point); 
    }
};

int main(int argc, char** argv){
    ros::init(argc, argv, "planning_node");
    planning_node n;
    ros::spin();
}
